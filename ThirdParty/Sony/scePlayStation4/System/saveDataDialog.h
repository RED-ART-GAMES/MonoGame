#pragma once

#include "predecls.h"
#include "commonDialog.h"

#include <save_data_dialog.h>
#include <sceerror.h>

namespace System {

class SaveData;

enum class SaveDataDialogSysMsg
{
	Invalid = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_INVALID,
	NoData = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_NODATA,
	Confirm = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_CONFIRM,
	Overwrite = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_OVERWRITE,
	NoSpace = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_NOSPACE,
	Progress = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_PROGRESS,
	FileCorrupted = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_FILE_CORRUPTED,
	Finished = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_FINISHED,
	NoSpaceContinuable = SCE_SAVE_DATA_DIALOG_SYSMSG_TYPE_NOSPACE_CONTINUABLE,
};

enum class SaveDataDialogType
{
	Invalid = SCE_SAVE_DATA_DIALOG_TYPE_INVALID,
	Save = SCE_SAVE_DATA_DIALOG_TYPE_SAVE,			
	Load = SCE_SAVE_DATA_DIALOG_TYPE_LOAD,
	Delete = SCE_SAVE_DATA_DIALOG_TYPE_DELETE,
};

enum class SaveDataDialogButtonId
{
	Invalid = SCE_SAVE_DATA_DIALOG_BUTTON_ID_INVALID,
	Ok = SCE_SAVE_DATA_DIALOG_BUTTON_ID_OK,			
	Yes = SCE_SAVE_DATA_DIALOG_BUTTON_ID_YES,
	No = SCE_SAVE_DATA_DIALOG_BUTTON_ID_NO,
};

class CS_API SaveDataDialog
{	
private:
	 SceSaveDataDialogParam  _openParam;
	 SceSaveDataDialogCloseParam _closeParam;
	 SceSaveDataDialogItems _items;
	 SceSaveDataTitleId _titleId;
	 SceSaveDataDirName _dirName;

	CS_IGNORE SaveDataDialog(const SaveDataDialog&) { } 

public:

	SaveDataDialog();
	~SaveDataDialog();

	CommonDialogError OpenSystemMsg(const SceSaveDataDialogType type,
		SaveData * saveData,
		SceSaveDataDialogSystemMessageType msgType,
		uint64_t value/*=0*/,
		void* newIconBuf/*=NULL*/, const size_t newIconSize/*=0*/);
	CommonDialogError OpenSystemWizardMsg(const SceSaveDataDialogType type,
		SaveData* saveData,
		SceSaveDataDialogSystemMessageType msgType,
		uint64_t value/*=0*/,
		void* newIconBuf/*=NULL*/, const size_t newIconSize/*=0*/);
	CommonDialogError OpenProgress(const SceSaveDataDialogType type, SaveData* saveData,
		SceSaveDataDialogProgressSystemMessageType msgType);
	CommonDialogError OpenError(const SceSaveDataDialogType type, SaveData* saveData, int errorCode);

	CommonDialogError ForceClose();

	CommonDialogStatus UpdateStatus();

	CommonDialogError GetResult(CS_OUT CommonDialogResult *result, CS_OUT SaveDataDialogButtonId *buttonId);

	void SetUserId(SceUserServiceUserId userId);
	SceUserServiceUserId GetUserId();

	void SetTitleId(const char* titleId);
	const char* GetTitleId();

	void SetDirectoryName(const char* dirName);
	const char* GetDirectoryName();

	void SetDisplayType(SaveDataDialogType type);
	SaveDataDialogType GetDisplayType();

	static SaveDataDialog* saveDataDialog;
};

} // namespace System
