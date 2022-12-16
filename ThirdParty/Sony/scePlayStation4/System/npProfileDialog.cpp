#include "npProfileDialog.h"
#include <libsysmodule.h>
#include <assert.h>

using namespace System;


CommonDialogError NpProfileDialog::Initialize()
{
	if (sceSysmoduleIsLoaded(SCE_SYSMODULE_NP_PROFILE_DIALOG) != SCE_SYSMODULE_LOADED)
	{
		auto error = sceSysmoduleLoadModule(SCE_SYSMODULE_NP_PROFILE_DIALOG);
		assert(error == SCE_OK);
	}

	auto error = sceNpProfileDialogInitialize();
	return (CommonDialogError)error;
}

CommonDialogError NpProfileDialog::Terminate()
{
	auto error = sceNpProfileDialogTerminate();
	return (CommonDialogError)error;
}

CommonDialogError NpProfileDialog::Open(NpProfileDialogMode mode, UserServiceUserId userId, SceNpAccountId targetAccountId, uint64_t userData)
{
	SceNpProfileDialogParamA param;
	sceNpProfileDialogParamInitializeA(&param);
#if SCE_ORBIS_SDK_VERSION >= 0x03008201u // SDK Version 3.0
	param.mode = (SceNpProfileDialogMode)mode;	
#else
	param.mode = (sceNpProfileDialogMode)mode;
#endif
	param.userId = (SceUserServiceUserId)userId;
	param.targetAccountId = targetAccountId;
	param.userData = (void*)userData;

	auto error = sceNpProfileDialogOpenA(&param);
	return (CommonDialogError)error;
}

CommonDialogError NpProfileDialog::Close()
{
	auto error = sceNpProfileDialogClose();
	return (CommonDialogError)error;
}

/*
CommonDialogError NpProfileDialog::GetResult(CS_OUT int32_t &result, CS_OUT CommonDialogResult &userAction, CS_OUT uint64_t &userData)
{
	SceNpProfileDialogResult params;
	auto error = sceNpProfileDialogGetResult(&params);
	if (error >= SCE_OK)
	{
		result = params.result;
		userAction = (CommonDialogResult)params.userAction;
		userData = (uint64_t)params.userData;
	}

	return (CommonDialogError)error;
}
*/

CommonDialogStatus NpProfileDialog::GetStatus()
{
	auto status = sceNpProfileDialogGetStatus();
	return (CommonDialogStatus)status;
}

CommonDialogStatus NpProfileDialog::UpdateStatus()
{
	auto status = sceNpProfileDialogUpdateStatus();
	return (CommonDialogStatus)status;
}