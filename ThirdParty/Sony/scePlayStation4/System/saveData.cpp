#include "saveData.h"

#include <memory.h>
#include <assert.h>

#include <save_data.h>
#include <scebase_common.h>
#include <error_dialog.h>

#include <string>

#include "saveDataDialog.h"

#if SCE_ORBIS_SDK_VERSION >= 0x04008081u
#define SceSaveDataMount SceSaveDataMount2
#define sceSaveDataMount sceSaveDataMount2
#endif

using namespace System;

bool SaveData::_initialized = false;


SaveDataResult SaveData::Initialize(ThreadPrio priority)
{
#if SCE_ORBIS_SDK_VERSION >= 0x03508041u // SDK Version 3.5
	//SceSaveDataInitParams3 params;
	//memset(&params, 0, sizeof(params));
	//params.priority = (int32_t)priority;
	auto result = sceSaveDataInitialize3(nullptr);
#else
	SceSaveDataInitParams params;
	memset(&params, 0, sizeof(params));
	params.priority = (int32_t)priority;
	auto result = sceSaveDataInitialize(&params);
#endif

	if (result == SCE_OK)
		_initialized = true;

	return (SaveDataResult)result;
}

SaveDataResult SaveData::Terminate()
{
	auto result = sceSaveDataTerminate();
	if (result == SCE_OK)
		_initialized = false;

	return (SaveDataResult)result;
}

bool SaveData::IsBackupAvailable()
{
	SceSaveDataCheckBackupData check;
	memset(&check, 0, sizeof(check));
	check.userId = _userId;
	check.dirName = _dirName.data[0] ? &_dirName : NULL;
	check.titleId = NULL;
	check.param = NULL;
	check.icon = NULL;

	return sceSaveDataCheckBackupData(&check) == SCE_OK;
}

void SaveData::RestoreBackup()
{
	SceSaveDataRestoreBackupData restore;
	memset(&restore, 0, sizeof(restore));
	restore.userId = _userId;
	restore.dirName = _dirName.data[0] ? &_dirName : NULL;
	restore.titleId = NULL;
	restore.fingerprint = NULL;
	
	sceSaveDataRestoreBackupData(&restore);
}

SaveData::SaveData(UserServiceUserId userId, const char *titleId, const char *dirName, const char *fingerprint)
{
	if (!_initialized)
		Initialize(ThreadPrio::Default);

	_userId = userId;

	memset(&_titleId, 0, sizeof(_titleId));
	if (titleId != NULL)
		strncpy(_titleId.data, titleId, SCE_SAVE_DATA_TITLE_ID_DATA_SIZE);
	memset(&_dirName, 0, sizeof(_dirName));
	if (dirName != NULL)
		strncpy(_dirName.data, dirName, SCE_SAVE_DATA_DIRNAME_DATA_MAXSIZE);
	memset(&_fingerprint, 0, sizeof(_fingerprint));
	if (fingerprint != NULL)
		strncpy(_fingerprint.data, fingerprint, SCE_SAVE_DATA_FINGERPRINT_DATA_SIZE);

	memset(&_mountPoint, 0, sizeof(_mountPoint));
	memset(_title, 0, sizeof(_title));
	memset(_subTitle, 0, sizeof(_subTitle));
	memset(_detail, 0, sizeof(_detail));
}

SaveData::~SaveData()
{
	if (_mountPoint.data[0] != 0)
		Unmount();
}

SaveDataResult SaveData::Mount(	uint64_t blocks,
								SaveDataMountMode mountMode,
								CS_OUT uint64_t &requiredBlocks,
								CS_OUT uint32_t &progress)
{
	SceSaveDataMount mount;
	memset(&mount, 0, sizeof(mount));
	mount.userId = _userId;
	mount.dirName = _dirName.data[0] ? &_dirName : NULL;
#if SCE_ORBIS_SDK_VERSION < 0x04008081u
	mount.titleId = _titleId.data[0] ? &_titleId : NULL;
	mount.fingerprint = _fingerprint.data[0] ? &_fingerprint : NULL;
#endif
	mount.blocks = blocks;
	mount.mountMode = (SceSaveDataMountMode)mountMode;

	SceSaveDataMountResult mountResult;
	memset(&mountResult, 0, sizeof(mountResult));

	SaveDataResult result = static_cast<SaveDataResult>(sceSaveDataMount(&mount, &mountResult));

	memcpy(&_mountPoint, &mountResult.mountPoint, sizeof(_mountPoint));
	requiredBlocks = mountResult.requiredBlocks;
#if SCE_ORBIS_SDK_VERSION >= 0x03508041u // SDK Version 3.5
	progress = 0;
#else
	progress = mountResult.progress;
#endif

	if (result == SaveDataResult::ErrorBroken)
	{
		SceSaveDataCheckBackupData backupData;
		memset(&backupData, 0, sizeof(backupData));
		backupData.dirName = mount.dirName;
		backupData.userId = mount.userId;
		if (sceSaveDataCheckBackupData(&backupData) == SCE_OK)
		{
			askForBackup:
			SceCommonDialogStatus status;
			SaveDataDialog::saveDataDialog->OpenSystemMsg(SCE_SAVE_DATA_DIALOG_TYPE_LOAD,
				this, SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_CORRUPTED_AND_RESTORE, 0, nullptr, 0);
			while ((status = sceSaveDataDialogUpdateStatus()) != SCE_COMMON_DIALOG_STATUS_FINISHED);
			SceSaveDataDialogResult res;
			memset(&res, 0, sizeof(res));
			sceSaveDataDialogGetResult(&res);
			if (res.result != SCE_OK) goto askForBackup;
			SceSaveDataRestoreBackupData restoreBackupData;
			memset(&restoreBackupData, 0, sizeof(restoreBackupData));
			restoreBackupData.dirName = mount.dirName;
			restoreBackupData.userId = mount.userId;
			if (sceSaveDataRestoreBackupData(&restoreBackupData) != SCE_OK)
				goto error;
			return Mount(blocks, mountMode, requiredBlocks, progress);
		}
		else
		{
		error:
			SaveDataDialog::saveDataDialog->OpenError(SCE_SAVE_DATA_DIALOG_TYPE_LOAD, this, (int)SaveDataResult::ErrorBroken);
		}
	}
	else if (result == SaveDataResult::ErrorNoSpaceFs)
	{
		SceCommonDialogStatus status;
		auto ret = SaveDataDialog::saveDataDialog->OpenSystemMsg(SCE_SAVE_DATA_DIALOG_TYPE_SAVE,
			this, SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_NOSPACE_CONTINUABLE, blocks, nullptr, 0);
		while ((status = sceSaveDataDialogUpdateStatus()) != SCE_COMMON_DIALOG_STATUS_FINISHED);
		return Mount(blocks, mountMode, requiredBlocks, progress);
	}

	return result;
}

SaveDataResult SaveData::Unmount(bool withBackup)
{
	if (withBackup) return UnmountWithBackup();
	auto result = sceSaveDataUmount(&_mountPoint);
	if (result == SCE_OK)
	{
		memset(&_mountPoint, 0, sizeof(_mountPoint));
		memset(_title, 0, sizeof(_title));
		memset(_subTitle, 0, sizeof(_subTitle));
		memset(_detail, 0, sizeof(_detail));
	}
	return (SaveDataResult)result;
}

SaveDataResult SaveData::UnmountWithBackup()
{
	auto result = sceSaveDataUmountWithBackup(&_mountPoint);
	if (result == SCE_OK)
	{
		memset(&_mountPoint, 0, sizeof(_mountPoint));
		memset(_title, 0, sizeof(_title));
		memset(_subTitle, 0, sizeof(_subTitle));
		memset(_detail, 0, sizeof(_detail));
	}
	return (SaveDataResult)result;
}

SaveDataResult SaveData::GetMountInfo(	CS_OUT uint64_t *blocks,
										CS_OUT uint64_t *freeBlocks)
{
	SceSaveDataMountInfo info;
	memset(&info, 0, sizeof(info));

	auto result = sceSaveDataGetMountInfo(&_mountPoint, &info);
	if (result >= SCE_OK)
	{
		*blocks = info.blocks;
		*freeBlocks = info.freeBlocks;
	}

	return (SaveDataResult)result;
}

const char* SaveData::GetMountPoint() const
{
	return _mountPoint.data;
}

const char* SaveData::GetTitle()
{
	auto result = sceSaveDataGetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_TITLE, _title, SCE_SAVE_DATA_TITLE_MAXSIZE, NULL);
	assert(result == SCE_OK);
	return _title;
}

const char* SaveData::GetSubTitle()
{
	auto result = sceSaveDataGetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_SUB_TITLE, _subTitle, SCE_SAVE_DATA_SUBTITLE_MAXSIZE, NULL);
	assert(result == SCE_OK);
	return _subTitle;
}

const char* SaveData::GetDetail()
{
	auto result = sceSaveDataGetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_DETAIL, _detail, SCE_SAVE_DATA_DETAIL_MAXSIZE, NULL);
	assert(result == SCE_OK);
	return _detail;
}

uint32_t SaveData::GetUserParam()
{
	uint32_t userParam;
	auto result = sceSaveDataGetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_USER_PARAM, &userParam, sizeof(uint32_t), NULL);
	assert(result == SCE_OK);
	return userParam;
}

time_t SaveData::GetMTime()
{
	time_t mtime;
	auto result = sceSaveDataGetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_MTIME, &mtime, sizeof(time_t), NULL);
	assert(result == SCE_OK);
	return mtime;

}

void SaveData::SetTitle(const char *title)
{
	auto len = strlen(title);
	assert(len < SCE_SAVE_DATA_TITLE_MAXSIZE);
	auto result = sceSaveDataSetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_TITLE, title, len);
	assert(result == SCE_OK);
}

void SaveData::SetSubTitle(const char *subTitle)
{
	auto len = strlen(subTitle);
	assert(len < SCE_SAVE_DATA_SUBTITLE_MAXSIZE);
	auto result = sceSaveDataSetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_SUB_TITLE, subTitle, len);
	assert(result == SCE_OK);
}

void SaveData::SetDetail(const char *detail)
{
	auto len = strlen(detail);
	assert(len < SCE_SAVE_DATA_DETAIL_MAXSIZE);
	auto result = sceSaveDataSetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_DETAIL, detail, len);
	assert(result == SCE_OK);
}

std::string GetDirFromFilePath(const std::string& str)
{
	size_t found;
	found = str.find_last_of("/\\");
	return str.substr(0, found);
}

bool SaveData::Write(const char* filePath, const void* buf, size_t nbytes) const
{
	int32_t ret = SCE_OK;

	std::string path = _mountPoint.data;
	path += "/";
	path += filePath;
	int fd = sceKernelOpen(path.c_str(), SCE_KERNEL_O_RDWR | SCE_KERNEL_O_TRUNC | SCE_KERNEL_O_CREAT, SCE_KERNEL_S_IRWU);
	if (fd < SCE_OK)
	{
		if (fd == SCE_KERNEL_ERROR_ENOENT) {
			std::string dirPath = GetDirFromFilePath(filePath);
			if (MkDir(dirPath.c_str())) return Write(filePath, buf, nbytes);
		}
		fprintf(stderr, "sceKernelOpen : 0x%08x(%s)\n", fd, path.c_str());
		return false;
	}
	ret = static_cast<int32_t>(sceKernelWrite(fd, buf, nbytes));
	if (ret < SCE_OK)
	{
		fprintf(stderr, "sceKernelWrite : 0x%08x(%s)\n", ret, path.c_str());
		sceKernelClose(fd);
		return ret == SCE_OK;
	}
	sceKernelClose(fd);
	fprintf(stderr, "sceKernelWriteWhat : 0x%08x(%s)\n", ret, path.c_str());

	return ret >= SCE_OK;
}

char * SaveData::Read(const char* filePath) const
{
	int32_t ret = SCE_OK;

	std::string path = _mountPoint.data;
	path += "/";
	path += filePath;
	SceKernelStat st;
	ret = sceKernelStat(path.c_str(), &st);
	if (ret < SCE_OK)
	{
		fprintf(stderr, "sceKernelStat : 0x%08x(%s)\n", ret, path.c_str());
		return nullptr;
	}

	char * data = new char[st.st_size];
	if (!data)
	{
		fprintf(stderr, "data == NULL\n");
		return nullptr;
	}

	int fd = sceKernelOpen(path.c_str(), SCE_KERNEL_O_RDONLY, SCE_KERNEL_S_INONE);
	if (fd < SCE_OK)
	{
		fprintf(stderr, "sceKernelOpen : 0x%08x(%s)\n", fd, path.c_str());
		delete[] data;
		return nullptr;
	}
	ret = static_cast<int32_t>(sceKernelRead(fd, data, static_cast<size_t>(st.st_size)));
	if (ret < SCE_OK)
	{
		fprintf(stderr, "sceKernelRead : 0x%08x(%s)\n", ret, path.c_str());
		goto End;
	}

	sceKernelClose(fd);
	return data;
End:
	sceKernelClose(fd);
	delete[] data;

	return nullptr;
}

void SaveData::FreeRead(char* data) const
{
	if (data) delete data;
}

bool SaveData::FileExists(const char* filePath) const
{
	std::string path = _mountPoint.data;
	path += "/";
	path += filePath;
	SceKernelStat st;
	int ret = sceKernelStat(path.c_str(), &st);
	return ret != SCE_KERNEL_ERROR_ENOENT;
}

bool SaveData::MkDir(const char* filePath) const
{
	std::string path = _mountPoint.data;
	path += "/";
	path += filePath;
	int ret = static_cast<int32_t>(sceKernelMkdir(path.c_str(), SCE_KERNEL_S_IRWU));
	if (ret < SCE_OK)
	{
		fprintf(stderr, "sceKernelMkDir : 0x%08x(%s)\n", ret, path.c_str());
		return false;
	}
	return true;
}

UserServiceUserId System::SaveData::GetUserId()
{
	return _userId;
}

SceSaveDataTitleId* System::SaveData::GetTitleId()
{
	return &_titleId;
}

SceSaveDataDirName* System::SaveData::GetDirName()
{
	return &_dirName;
}

void SaveData::SetUserParam(uint32_t userParam)
{
	auto result = sceSaveDataSetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_USER_PARAM, &userParam, sizeof(uint32_t));
	assert(result == SCE_OK);
}

void SaveData::SetMTime(time_t mtime)
{
	auto result = sceSaveDataSetParam(&_mountPoint, SCE_SAVE_DATA_PARAM_TYPE_MTIME, &mtime, sizeof(time_t));
	assert(result == SCE_OK);
}

SaveDataResult SaveData::_LoadIcon(void *buffer, size_t bufferSize, CS_OUT size_t *dataSize)
{
	SceSaveDataIcon icon;
	memset(&icon, 0, sizeof(icon));
	icon.buf = buffer;
	icon.bufSize = bufferSize;

	auto result = sceSaveDataLoadIcon(&_mountPoint, &icon);
	if (result >= SCE_OK)
		*dataSize = icon.dataSize;

	return (SaveDataResult)result;
}

SaveDataResult SaveData::_SaveIcon(void *buffer, size_t bufferSize)
{
	SceSaveDataIcon icon;
	memset(&icon, 0, sizeof(icon));
	icon.buf = buffer;
	icon.bufSize = bufferSize;
	icon.dataSize = bufferSize;

	auto result = sceSaveDataSaveIcon(&_mountPoint, &icon);
	return (SaveDataResult)result;
}

SaveDataResult SaveData::Delete(	UserServiceUserId userId, 
									const char *titleId, 
									const char *dirName, 
									CS_OUT uint32_t *progress)
{
	SceSaveDataTitleId title;
	if (titleId != NULL)
	{
		memset(&title, 0, sizeof(title));
		strncpy(title.data, titleId, SCE_SAVE_DATA_TITLE_ID_DATA_SIZE);
	}

	SceSaveDataDirName dir;
	if (dirName != NULL)
	{
		memset(&dir, 0, sizeof(dir));
		strncpy(dir.data, dirName, SCE_SAVE_DATA_DIRNAME_DATA_MAXSIZE);
	}

	SceSaveDataDelete delete_;
	memset(&delete_, 0, sizeof(delete_));
	delete_.userId = userId;
	delete_.titleId = titleId ? &title : NULL; 
	delete_.dirName = dirName ? &dir : NULL;

	auto result = sceSaveDataDelete(&delete_);
	if (result >= SCE_OK)
	{
#if SCE_ORBIS_SDK_VERSION >= 0x03508041u // SDK Version 3.5
		*progress = 0;
#else
		*progress = delete_.progress;
#endif
	}

	return (SaveDataResult)result;
}
