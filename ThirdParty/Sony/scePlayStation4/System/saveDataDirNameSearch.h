#pragma once

#include "predecls.h"

#include <string.h>

#include <scebase.h>
#include <save_data.h>

namespace System {

enum class SaveDataResult;


enum class SaveDataSortKey  
{
	DirName = SCE_SAVE_DATA_SORT_KEY_DIRNAME,
	UserParam = SCE_SAVE_DATA_SORT_KEY_USER_PARAM,
	MTime = SCE_SAVE_DATA_SORT_KEY_MTIME,
#if SCE_ORBIS_SDK_VERSION >= 0x03508041u // SDK Version 3.5
	Blocks = SCE_SAVE_DATA_SORT_KEY_BLOCKS,
	FreeBlocks = SCE_SAVE_DATA_SORT_KEY_FREE_BLOCKS,
#else
	SizeKib = SCE_SAVE_DATA_SORT_KEY_SIZE_KIB,
#endif
};

enum class SaveDataSortOrder  
{
	Ascent = SCE_SAVE_DATA_SORT_ORDER_ASCENT,
	Descent = SCE_SAVE_DATA_SORT_ORDER_DESCENT,
};


class CS_API SaveDataDirNameSearch
{
private:

	int _maxResults;

	SceSaveDataTitleId _titleId;
	SceSaveDataDirName _dirName;
	SceSaveDataDirName *_names;
	SceSaveDataParam *_params;
	SceSaveDataDirNameSearchCond  _cond;
	SceSaveDataDirNameSearchResult _results;

	CS_IGNORE SaveDataDirNameSearch(const SaveDataDirNameSearch&) { } 

public:

	SaveDataDirNameSearch(SceUserServiceUserId userId, int maxResults);
	~SaveDataDirNameSearch();

	SaveDataResult Search(const char *dirNameOrNull);

	int GetHits();

	const char* GetDirName(int index);
	const char* GetTitle(int index);
	const char* GetSubTitle(int index);
	const char* GetDetail(int index);
	uint32_t GetUserParam(int index);
	time_t GetModifiedTime(int index);

	void SetSortKey(SaveDataSortKey key);
	SaveDataSortKey GetSortKey();

	void SetSortOrder(SaveDataSortOrder order);
	SaveDataSortOrder GetSortOrder();

	void SetTitleId(const char *titleId);
	const char* GetTitleId();

};

} // namespace System
