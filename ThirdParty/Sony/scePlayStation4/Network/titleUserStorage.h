#pragma once

#include "predecls.h"
#include <scebase.h>
#include <np.h>

namespace Network {

enum class TitleUserStorageResult
{
	Ok = SCE_OK,

	ErrorNotInitialized = SCE_NP_COMMUNITY_ERROR_NOT_INITIALIZED,
	ErrorOutOfMemory = SCE_NP_COMMUNITY_ERROR_OUT_OF_MEMORY,
	ErrorInvalidArgument = SCE_NP_COMMUNITY_ERROR_INVALID_ARGUMENT,
	ErrorTooManyObjects = SCE_NP_COMMUNITY_ERROR_TOO_MANY_OBJECTS,
	ErrorAborted = SCE_NP_COMMUNITY_ERROR_ABORTED,
	ErrorBodyTooLarge = SCE_NP_COMMUNITY_ERROR_BODY_TOO_LARGE,
	ErrorInsufficientArgument = SCE_NP_COMMUNITY_ERROR_INSUFFICIENT_ARGUMENT,
	ErrorInvalidId = SCE_NP_COMMUNITY_ERROR_INVALID_ID,
	ErrorInvalidAlignment = SCE_NP_COMMUNITY_ERROR_INVALID_ALIGNMENT,
	ErrorServerErrorBadRequest = SCE_NP_COMMUNITY_SERVER_ERROR_BAD_REQUEST,
	ErrorServerErrorForbidden = SCE_NP_COMMUNITY_SERVER_ERROR_FORBIDDEN,
	ErrorServerErrorInvalidAntiCheatData = SCE_NP_COMMUNITY_SERVER_ERROR_INVALID_ANTICHEAT_DATA,
	ErrorServerErrorNoSuchTitle = SCE_NP_COMMUNITY_SERVER_ERROR_NO_SUCH_TITLE,
	ErrorServerErrorTitleUserStorageBeforeService = SCE_NP_COMMUNITY_SERVER_ERROR_TITLE_USER_STORAGE_BEFORE_SERVICE,
	ErrorServerErrorTitleUserStorageEndOfService = SCE_NP_COMMUNITY_SERVER_ERROR_TITLE_USER_STORAGE_END_OF_SERVICE,
	ErrorServerErrorTitleUserStorageMaintenance = SCE_NP_COMMUNITY_SERVER_ERROR_TITLE_USER_STORAGE_MAINTENANCE,
	ErrorServerErrorUserNotAssigned = SCE_NP_COMMUNITY_SERVER_ERROR_USER_NOT_ASSIGNED,
	ErrorServerErrorUserStorageTitleMasterNotFound = SCE_NP_COMMUNITY_SERVER_ERROR_USER_STORAGE_TITLE_MASTER_NOT_FOUND,
	ErrorServerErrorInvalidVirtualUser = SCE_NP_COMMUNITY_SERVER_ERROR_INVALID_VIRTUAL_USER,
	ErrorServerErrorStorageDataNotFound = SCE_NP_COMMUNITY_SERVER_ERROR_USER_STORAGE_DATA_NOT_FOUND,
	ErrorServerErrorTooLargeData = SCE_NP_COMMUNITY_SERVER_ERROR_TOO_LARGE_DATA,
};

class CS_API TitleUserStorage
{
	CS_IGNORE SceNpId _npId;
	int32_t _titleCtxId;

	TitleUserStorage(const TitleUserStorage&) { }

public:

	TitleUserStorage();
	~TitleUserStorage();

	TitleUserStorageResult CreateContext(const SceUserServiceUserId userId, const SceNpServiceLabel serviceLabel);

	TitleUserStorageResult GetData(SceNpAccountId targetAccountId, SceNpTusSlotId slotId, void* buffer, size_t bufferSize, CS_OUT size_t* recvdSize);
	TitleUserStorageResult SetData(SceNpAccountId targetAccountId, SceNpTusSlotId slotId, void* buffer, size_t bufferSize);
	TitleUserStorageResult DeleteData(SceNpAccountId targetAccountId, SceNpTusSlotId slotId);
};

} // namespace Network
