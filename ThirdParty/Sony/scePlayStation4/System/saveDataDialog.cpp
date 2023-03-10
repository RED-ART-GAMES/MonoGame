#include "saveDataDialog.h"
#include <libsysmodule.h>
#include <assert.h>
#include <sys/param.h>

#include "saveData.h"

using namespace System;

SaveDataDialog * SaveDataDialog::saveDataDialog = nullptr;

SaveDataDialog::SaveDataDialog()
{
	sceSaveDataDialogParamInitialize(&_openParam);

	memset(&_closeParam, 0, sizeof(_closeParam));
	memset(&_items, 0, sizeof(_items));
	memset(&_titleId, 0, sizeof(_titleId));
	memset(&_dirName, 0, sizeof(_dirName));

	_items.dirName = &_dirName;

	_openParam.items = &_items;
	_openParam.dispType = SCE_SAVE_DATA_DIALOG_TYPE_SAVE;

	sceSysmoduleLoadModule(SCE_SYSMODULE_SAVE_DATA_DIALOG);
	auto error = sceSaveDataDialogInitialize();
	fprintf(stderr, "SaveDataDialog::Init = %#010x\n", error);
	assert(error == SCE_OK);
	saveDataDialog = this;
}

SaveDataDialog::~SaveDataDialog()
{
	auto error = sceSaveDataDialogTerminate();
	saveDataDialog = nullptr;
	assert(error == SCE_OK);
}

CommonDialogError SaveDataDialog::OpenSystemMsg(
	const SceSaveDataDialogType type,
	SaveData * saveData,
	SceSaveDataDialogSystemMessageType msgType,
	uint64_t value/*=0*/,
	void* newIconBuf/*=NULL*/, const size_t newIconSize/*=0*/)
{
	SceUserServiceUserId userId = saveData->GetUserId();
	SceSaveDataTitleId* titleId = nullptr; saveData->GetTitleId();
	SceSaveDataDirName* dirName = saveData->GetDirName();
	_openParam.mode = SCE_SAVE_DATA_DIALOG_MODE_SYSTEM_MSG;
	_openParam.dispType = type;

	SceSaveDataDialogAnimationParam animParam;
	memset(&animParam, 0x00, sizeof(animParam));
	animParam.userOK = SCE_SAVE_DATA_DIALOG_ANIMATION_ON;
	animParam.userCancel = SCE_SAVE_DATA_DIALOG_ANIMATION_OFF;
	_openParam.animParam = &animParam;

	bool showNewItem = false;
	SceSaveDataDialogNewItem newItem;
	memset(&newItem, 0x00, sizeof(newItem));
	if (newIconBuf)
	{
		newItem.title = "New Save Data";
		newItem.iconBuf = static_cast<void*>(newIconBuf);
		newItem.iconSize = newIconSize;
		showNewItem = true;
	}

	SceSaveDataDialogItems items;
	memset(&items, 0x00, sizeof(items));
	items.userId = userId;
	items.titleId = titleId;
	items.dirName = dirName;
	if (dirName)
	{
		items.dirNameNum = dirName->data[0] == '\0' ? 0 : 1;
	}
	items.newItem = showNewItem ? &newItem : NULL;

	SceSaveDataDialogSystemMessageParam sysMessageParam;
	memset(&sysMessageParam, 0x00, sizeof(sysMessageParam));
	sysMessageParam.sysMsgType = msgType;
	sysMessageParam.value = value;

	_openParam.items = &items;
	_openParam.sysMsgParam = &sysMessageParam;

	auto error = sceSaveDataDialogOpen(&_openParam);

	return (CommonDialogError)error;
}

CommonDialogError SaveDataDialog::OpenSystemWizardMsg(
	const SceSaveDataDialogType type,
	SaveData* saveData,
	SceSaveDataDialogSystemMessageType msgType,
	uint64_t value/*=0*/,
	void* newIconBuf/*=NULL*/, const size_t newIconSize/*=0*/)
{
	//sceSaveDataDialogParamInitialize(&_openParam);
	memset(&_openParam, 0x00, sizeof(_openParam));

	SceUserServiceUserId userId = saveData->GetUserId();
	SceSaveDataTitleId* titleId = nullptr; saveData->GetTitleId();
	SceSaveDataDirName* dirName = saveData->GetDirName();
	_openParam.mode = SCE_SAVE_DATA_DIALOG_MODE_WIZARD_CONFIRM;
	_openParam.dispType = type;

	SceSaveDataDialogAnimationParam animParam;
	memset(&animParam, 0x00, sizeof(animParam));
	animParam.userOK = SCE_SAVE_DATA_DIALOG_ANIMATION_ON;
	animParam.userCancel = SCE_SAVE_DATA_DIALOG_ANIMATION_ON;
	_openParam.animParam = &animParam;

	//bool showNewItem = false;
	//SceSaveDataDialogNewItem newItem;
	//memset(&newItem, 0x00, sizeof(newItem));
	//if (newIconBuf)
	//{
	//	newItem.title = "New Save Data";
	//	newItem.iconBuf = static_cast<void*>(newIconBuf);
	//	newItem.iconSize = newIconSize;
	//	showNewItem = true;
	//}

	SceSaveDataDialogItems items;
	memset(&items, 0x00, sizeof(items));
	items.userId = userId;
	items.titleId = titleId;
	items.dirName = dirName;
	items.dirNameNum = 1;
	items.newItem = NULL;

	_openParam.items = &items;

	SceSaveDataDialogWizardParam wizParam;
	memset(&wizParam, 0x00, sizeof(wizParam));
	wizParam.option = SCE_SAVE_DATA_DIALOG_WIZARD_OPTION_RESTORE_OR_CORRUPTED;
	_openParam.wizardParam = &wizParam;

	auto error = sceSaveDataDialogOpen(&_openParam);

	return (CommonDialogError)error;
}

CommonDialogError System::SaveDataDialog::OpenProgress(const SceSaveDataDialogType type, SaveData* saveData, SceSaveDataDialogProgressSystemMessageType msgType)
{
	memset(&_openParam, 0x00, sizeof(_openParam));
	SceUserServiceUserId userId = saveData->GetUserId();
	SceSaveDataTitleId* titleId = nullptr; saveData->GetTitleId();
	SceSaveDataDirName* dirName = saveData->GetDirName();
	_openParam.mode = SCE_SAVE_DATA_DIALOG_MODE_PROGRESS_BAR;
	_openParam.dispType = type;

	SceSaveDataDialogAnimationParam animParam;
	memset(&animParam, 0x00, sizeof(animParam));
	animParam.userOK = SCE_SAVE_DATA_DIALOG_ANIMATION_ON;
	animParam.userCancel = SCE_SAVE_DATA_DIALOG_ANIMATION_ON;
	_openParam.animParam = &animParam;

	SceSaveDataDialogItems items;
	memset(&items, 0x00, sizeof(items));
	items.userId = userId;
	items.titleId = titleId;
	items.dirName = dirName;
	if (dirName)
	{
		items.dirNameNum = dirName->data[0] == '\0' ? 0 : 1;
	}
	items.newItem = NULL;

	SceSaveDataDialogProgressBarParam progParam;
	memset(&progParam, 0x00, sizeof(progParam));
	progParam.sysMsgType = msgType;
	progParam.barType = SCE_SAVE_DATA_DIALOG_PROGRESSBAR_TYPE_PERCENTAGE;

	_openParam.items = &items;
	_openParam.progBarParam = &progParam;

	auto error = sceSaveDataDialogOpen(&_openParam);

	return (CommonDialogError)error;
}

CommonDialogError System::SaveDataDialog::OpenError(const SceSaveDataDialogType type, SaveData* saveData, int errorCode)
{
	memset(&_openParam, 0x00, sizeof(_openParam));
	SceUserServiceUserId userId = saveData->GetUserId();
	SceSaveDataTitleId* titleId = nullptr; saveData->GetTitleId();
	SceSaveDataDirName* dirName = saveData->GetDirName();
	_openParam.mode = SCE_SAVE_DATA_DIALOG_MODE_PROGRESS_BAR;
	_openParam.dispType = type;

	SceSaveDataDialogItems items;
	memset(&items, 0x00, sizeof(items));
	items.userId = userId;
	items.titleId = titleId;
	items.dirName = dirName;
	if (dirName)
	{
		items.dirNameNum = dirName->data[0] == '\0' ? 0 : 1;
	}
	items.newItem = NULL;

	SceSaveDataDialogErrorCodeParam errorCodeParam;
	memset(&errorCodeParam, 0x00, sizeof(errorCodeParam));
	errorCodeParam.errorCode = errorCode;

	_openParam.items = &items;
	_openParam.errorCodeParam = &errorCodeParam;

	auto error = sceSaveDataDialogOpen(&_openParam);

	return (CommonDialogError)error;
}

CommonDialogError SaveDataDialog::ForceClose()
{
	auto error = sceSaveDataDialogClose(&_closeParam);
	return (CommonDialogError)error;
}

CommonDialogStatus SaveDataDialog::UpdateStatus()
{
	auto status = sceSaveDataDialogUpdateStatus();
	return (CommonDialogStatus)status;
}

CommonDialogError SaveDataDialog::GetResult(CS_OUT CommonDialogResult *result, CS_OUT SaveDataDialogButtonId *buttonId)
{
	SceSaveDataDialogResult sdr;
	memset(&sdr, 0, sizeof(sdr));
	auto error = sceSaveDataDialogGetResult(&sdr);

	*result = (CommonDialogResult)sdr.result;
	*buttonId = (SaveDataDialogButtonId)sdr.buttonId;

	return (CommonDialogError)error;
}

void SaveDataDialog::SetUserId(SceUserServiceUserId userId)
{
	_items.userId = userId;
}

SceUserServiceUserId SaveDataDialog::GetUserId()
{
	return _items.userId;
}

void SaveDataDialog::SetTitleId(const char* titleId)
{
	if (titleId == nullptr)
		_items.titleId = nullptr;
	else
	{
		auto len = MIN(strlen(titleId), SCE_SAVE_DATA_TITLE_ID_DATA_SIZE-1);
		memcpy(_titleId.data, titleId, len);
		_items.titleId = &_titleId;
	}
}

const char* SaveDataDialog::GetTitleId()
{
	return _titleId.data;
}

void SaveDataDialog::SetDirectoryName(const char* dirName)
{
	auto len = MIN(strlen(dirName), SCE_SAVE_DATA_DIRNAME_DATA_MAXSIZE);
	strncpy(_dirName.data, dirName, len);
	_items.dirNameNum = dirName == nullptr ? 0 : 1;
}

const char* SaveDataDialog::GetDirectoryName()
{
	return _dirName.data;
}

void SaveDataDialog::SetDisplayType(SaveDataDialogType type)
{
	_openParam.dispType = (SceSaveDataDialogType)type;
}

SaveDataDialogType SaveDataDialog::GetDisplayType()
{
	return (SaveDataDialogType)_openParam.dispType;
}
