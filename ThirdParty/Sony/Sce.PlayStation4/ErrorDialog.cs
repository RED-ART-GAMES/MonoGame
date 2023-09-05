//----------------------------------------------------------------------------
// This is autogenerated code by CppSharp.
// Do not edit this file or all your changes will be lost after re-generation.
//----------------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Security;

namespace Sce.PlayStation4
{
    namespace System
    {
        public enum ErrorDialogError
        {
            Ok = 0,
            NotInitialized = -2131951615,
            AlreadyInitialized = -2131951614,
            InvalidState = -2131951611,
            ServiceBusy = -2131951610,
            ParamInvalid = -2131951613,
            UnexpectedFatal = -2131951612,
            InvalidUserId = -2131951609
        }

        public enum ErrorDialogStatus
        {
            None = 0,
            Initialized = 1,
            Running = 2,
            Finished = 3
        }

        public unsafe static partial class ErrorDialog
        {
            [StructLayout(LayoutKind.Explicit, Size = 1)]
            public partial struct Internal
            {
                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System11ErrorDialog10InitializeEv")]
                internal static extern System.ErrorDialogError Initialize_0();

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System11ErrorDialog9TerminateEv")]
                internal static extern System.ErrorDialogError Terminate_0();

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System11ErrorDialog4OpenEii")]
                internal static extern System.ErrorDialogError Open_0(int errorCode, int userId);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System11ErrorDialog5CloseEv")]
                internal static extern System.ErrorDialogError Close_0();

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System11ErrorDialog12UpdateStatusEv")]
                internal static extern System.ErrorDialogStatus UpdateStatus_0();

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System11ErrorDialog9GetStatusEv")]
                internal static extern System.ErrorDialogStatus GetStatus_0();
            }

            public static System.ErrorDialogError Initialize()
            {
                var __ret = Internal.Initialize_0();
                return __ret;
            }

            public static System.ErrorDialogError Terminate()
            {
                var __ret = Internal.Terminate_0();
                return __ret;
            }

            public static System.ErrorDialogError Open(int errorCode, int userId)
            {
                var arg0 = errorCode;
                var arg1 = userId;
                var __ret = Internal.Open_0(arg0, arg1);
                return __ret;
            }

            public static System.ErrorDialogError Close()
            {
                var __ret = Internal.Close_0();
                return __ret;
            }

            public static System.ErrorDialogStatus UpdateStatus()
            {
                var __ret = Internal.UpdateStatus_0();
                return __ret;
            }

            public static System.ErrorDialogStatus Status
            {
                get
                {
                    var __ret = Internal.GetStatus_0();
                    return __ret;
                }
            }
        }
    }
}