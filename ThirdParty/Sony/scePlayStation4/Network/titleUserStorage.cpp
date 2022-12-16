#include "titleUserStorage.h"

#include <libsysmodule.h>
#include <assert.h>
#include <memory>
#include <np.h>
#include <user_service.h>
#include <np.h>


#pragma comment(lib, "libSceNpCommon_stub_weak.a")
#pragma comment(lib, "libSceNpTus_stub_weak.a")
#pragma comment(lib, "libSceSysmodule_stub_weak.a")
#pragma comment(lib, "libSceNetCtl_stub_weak.a")
#pragma comment(lib, "libSceNpManager_stub_weak.a")


using namespace Network;

TitleUserStorage::TitleUserStorage()
	: _titleCtxId(-1)
{
	if (sceSysmoduleIsLoaded(SCE_SYSMODULE_NP_TUS) != SCE_SYSMODULE_LOADED)
	{
		auto ret = sceSysmoduleLoadModule(SCE_SYSMODULE_NP_TUS);
		assert(ret == SCE_OK);
	}
}

TitleUserStorage::~TitleUserStorage()
{
	if (_titleCtxId != -1)
	{
		auto ret = sceNpTusDeleteNpTitleCtx(_titleCtxId);
		assert(ret >= 0);
		_titleCtxId = -1;
	}
}

TitleUserStorageResult TitleUserStorage::CreateContext(const SceUserServiceUserId userId, const SceNpServiceLabel serviceLabel)
{
	if (_titleCtxId != -1)
	{
		auto ret = sceNpTusDeleteNpTitleCtx(_titleCtxId);
		assert(ret >= 0);
		_titleCtxId = -1;
	}

	auto ret = sceNpTusCreateNpTitleCtxA(serviceLabel, userId);
	if (ret < 0)
		return (TitleUserStorageResult)ret;

	_titleCtxId = ret;

	return TitleUserStorageResult::Ok;
}

TitleUserStorageResult TitleUserStorage::GetData(SceNpAccountId targetAccountId, SceNpTusSlotId slotId, void* buffer, size_t bufferSize, CS_OUT size_t* recvdSize)
{
	if (_titleCtxId == -1)
		return TitleUserStorageResult::ErrorNotInitialized;

	auto reqId = sceNpTusCreateRequest(_titleCtxId);
	if (reqId < 0)
		return (TitleUserStorageResult)reqId;

	SceNpTusDataStatusA dataStatus;
	memset(&dataStatus, 0, sizeof(dataStatus));

	auto ret = sceNpTusGetDataA(
		reqId, 
		targetAccountId,
		slotId,
		&dataStatus, 
		sizeof(dataStatus),
		buffer,
		bufferSize,
		NULL
		);

	sceNpTusDeleteRequest(reqId);

	if (ret < 0)
	{
		*recvdSize = 0;
		(TitleUserStorageResult)ret;
	}

	*recvdSize = ret;
	return TitleUserStorageResult::Ok;
}

TitleUserStorageResult TitleUserStorage::SetData(SceNpAccountId targetAccountId, SceNpTusSlotId slotId, void* buffer, size_t bufferSize)
{
	if (_titleCtxId == -1)
		return TitleUserStorageResult::ErrorNotInitialized;	
	
	auto reqId = sceNpTusCreateRequest(_titleCtxId);
	if (reqId < 0)
		return (TitleUserStorageResult)reqId;

	auto ret = sceNpTusSetDataA(
		reqId, 
		targetAccountId,
		slotId,				// slotId
		bufferSize,			// totalSize
		bufferSize,			// sendSize
		buffer,
		NULL,				// info
		0,				    // infoSize
		NULL,				// isLastChangedAuthor		
		NULL,				// isLastChangedDate - always null
		NULL				// option - always null
		);

	sceNpTusDeleteRequest(reqId);

	return (TitleUserStorageResult)ret;	

}

TitleUserStorageResult TitleUserStorage::DeleteData(SceNpAccountId targetAccountId, SceNpTusSlotId slotId)
{
	if (_titleCtxId == -1)
		return TitleUserStorageResult::ErrorNotInitialized;

	auto reqId = sceNpTusCreateRequest(_titleCtxId);
	if (reqId < 0)
		return (TitleUserStorageResult)reqId;

	SceNpTusSlotId slotIdArray[] = { slotId };

	auto ret = sceNpTusDeleteMultiSlotDataA(
		reqId,
		targetAccountId,
		slotIdArray,
		1,
		NULL);

	sceNpTusDeleteRequest(reqId);

	return (TitleUserStorageResult)ret;
}