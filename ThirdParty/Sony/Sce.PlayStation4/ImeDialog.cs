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
        public enum ImeError
        {
            Ok = 0,
            Busy = -2135162879,
            NotOpened = -2135162878,
            NoMemory = -2135162877,
            ConnectionFailed = -2135162876,
            TooManyRequests = -2135162875,
            InvalidText = -2135162874,
            EventOverflow = -2135162873,
            NotActive = -2135162872,
            ImeSuspending = -2135162871,
            DeviceInUse = -2135162870,
            InvalidUserId = -2135162864,
            InvalidType = -2135162863,
            InvalidSupportedLanguages = -2135162862,
            InvalidEnterLabel = -2135162861,
            InvalidInputMethod = -2135162860,
            InvalidOption = -2135162859,
            InvalidMaxTextLength = -2135162858,
            InvalidInputTextBuffer = -2135162857,
            InvalidPosX = -2135162856,
            InvalidPosY = -2135162855,
            InvalidHorizontalAlignment = -2135162854,
            InvalidVerticalAlignment = -2135162853,
            InvalidExtended = -2135162852,
            InvalidWork = -2135162848,
            InvalidArg = -2135162847,
            InvalidHandler = -2135162846,
            InvalidNoResourceId = -2135162845,
            InvalidMode = -2135162844,
            InvalidParam = -2135162832,
            InvalidAddress = -2135162831,
            InvalidReserved = -2135162830,
            InvalidTiming = -2135162829,
            InvalidInternal = -2135162625,
            InvalidKeyboardType = -2135162851
        }

        public enum ImeDialogStatus
        {
            None = 0,
            Running = 1,
            Finished = 2
        }

        public enum ImeDialogEndStatus
        {
            Ok = 0,
            Canceled = 1,
            Aborted = 2
        }

        public enum ImeDialogType
        {
            Default = 0,
            BasicLatin = 1,
            Url = 2,
            Main = 3,
            Number = 4
        }

        [Flags]
        public enum ImeLanguage : ulong
        {
            All = 0,
            Danish = 1,
            German = 2,
            EnglishUS = 4,
            EnglishGB = 262144,
            Spanish = 8,
            SpanishLA = 1048576,
            French = 16,
            Italian = 32,
            Dutch = 64,
            Norwegian = 128,
            Polish = 256,
            PortuguesePT = 512,
            PortugueseBR = 131072,
            Russian = 1024,
            Finnish = 2048,
            Swedish = 4096,
            Japanese = 8192,
            Korean = 16384,
            ChineseSimplified = 32768,
            ChineseTraditional = 65536,
            Turkish = 524288
        }

        public enum ImeEnterLabel
        {
            Default = 0,
            Send = 1,
            Search = 2,
            Go = 3
        }

        [Flags]
        public enum ImeOption
        {
            Default = 0,
            Multiline = 1,
            NoAutoCapitalization = 2,
            Password = 4,
            LanguagesForced = 8,
            ExtKeyboard = 16,
            NoLearning = 32,
            FixedPosition = 64,
            DisableCopyPaste = 128,
            DisableResume = 256
        }

        public enum ImeHorizontalAlignment
        {
            Left = 0,
            Center = 1,
            Right = 2
        }

        public enum ImeVerticalAlignment
        {
            Top = 0,
            Center = 1,
            Bottom = 2
        }

        public unsafe partial class ImeDialog : IDisposable
        {
            [StructLayout(LayoutKind.Explicit, Size = 11312)]
            public partial struct Internal
            {
                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialogC2ERKS0_")]
                internal static extern void cctor_0(global::System.IntPtr instance, global::System.IntPtr _0);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialogC2Ev")]
                internal static extern void ctor_1(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialogD2Ev")]
                internal static extern void dtor_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog4InitEv")]
                internal static extern System.ImeError Init_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog5AbortEv")]
                internal static extern System.ImeError Abort_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog4TermEv")]
                internal static extern System.ImeError Term_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog9GetResultEPNS_18ImeDialogEndStatusE")]
                internal static extern System.ImeError GetResult_0(global::System.IntPtr instance, System.ImeDialogEndStatus* result);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog9GetStatusEv")]
                internal static extern System.ImeDialogStatus GetStatus_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog9SetUserIdEi")]
                internal static extern void SetUserId_0(global::System.IntPtr instance, int userId);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog13GetDialogTypeEv")]
                internal static extern System.ImeDialogType GetDialogType_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog13SetDialogTypeENS_13ImeDialogTypeE")]
                internal static extern void SetDialogType_0(global::System.IntPtr instance, System.ImeDialogType type);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog21GetSupportedLanguagesEv")]
                internal static extern System.ImeLanguage GetSupportedLanguages_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog21SetSupportedLanguagesENS_11ImeLanguageE")]
                internal static extern void SetSupportedLanguages_0(global::System.IntPtr instance, System.ImeLanguage lang);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog13GetEnterLabelEv")]
                internal static extern System.ImeEnterLabel GetEnterLabel_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog13SetEnterLabelENS_13ImeEnterLabelE")]
                internal static extern void SetEnterLabel_0(global::System.IntPtr instance, System.ImeEnterLabel label);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog10GetOptionsEv")]
                internal static extern System.ImeOption GetOptions_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog10SetOptionsENS_9ImeOptionE")]
                internal static extern void SetOptions_0(global::System.IntPtr instance, System.ImeOption options);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog16GetMaxTextLengthEv")]
                internal static extern uint GetMaxTextLength_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog16SetMaxTextLengthEj")]
                internal static extern void SetMaxTextLength_0(global::System.IntPtr instance, uint length);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog12GetPositionXEv")]
                internal static extern float GetPositionX_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog12SetPositionXEf")]
                internal static extern void SetPositionX_0(global::System.IntPtr instance, float x);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog12GetPositionYEv")]
                internal static extern float GetPositionY_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog12SetPositionYEf")]
                internal static extern void SetPositionY_0(global::System.IntPtr instance, float y);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog22GetHorizontalAlignmentEv")]
                internal static extern System.ImeHorizontalAlignment GetHorizontalAlignment_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog22SetHorizontalAlignmentENS_22ImeHorizontalAlignmentE")]
                internal static extern void SetHorizontalAlignment_0(global::System.IntPtr instance, System.ImeHorizontalAlignment align);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog20GetVerticalAlignmentEv")]
                internal static extern System.ImeVerticalAlignment GetVerticalAlignment_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog20SetVerticalAlignmentENS_20ImeVerticalAlignmentE")]
                internal static extern void SetVerticalAlignment_0(global::System.IntPtr instance, System.ImeVerticalAlignment align);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog14GetPlaceholderEv")]
                internal static extern global::System.IntPtr GetPlaceholder_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog14SetPlaceholderEPKc")]
                internal static extern void SetPlaceholder_0(global::System.IntPtr instance, global::System.IntPtr text);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog8GetTitleEv")]
                internal static extern global::System.IntPtr GetTitle_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog8SetTitleEPKc")]
                internal static extern void SetTitle_0(global::System.IntPtr instance, global::System.IntPtr text);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog12GetInputTextEv")]
                internal static extern global::System.IntPtr GetInputText_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System9ImeDialog12SetInputTextEPKc")]
                internal static extern void SetInputText_0(global::System.IntPtr instance, global::System.IntPtr text);
            }

            public global::System.IntPtr __Instance { get; protected set; }

            internal ImeDialog(ImeDialog.Internal* native)
                : this(new global::System.IntPtr(native))
            {
            }

            internal ImeDialog(ImeDialog.Internal native)
                : this(&native)
            {
            }

            public ImeDialog(global::System.IntPtr native, bool isInternalImpl = false)
            {
                __Instance = native;
            }

            public ImeDialog()
            {
                __Instance = Marshal.AllocHGlobal(11312);
                Internal.ctor_1(__Instance);
            }

            public void Dispose()
            {
                Dispose(disposing: true);
                GC.SuppressFinalize(this);
            }

            protected virtual void Dispose(bool disposing)
            {
                Internal.dtor_0(__Instance);
                Marshal.FreeHGlobal(__Instance);
            }

            public System.ImeError Init()
            {
                var __ret = Internal.Init_0(__Instance);
                return __ret;
            }

            public System.ImeError Abort()
            {
                var __ret = Internal.Abort_0(__Instance);
                return __ret;
            }

            public System.ImeError Term()
            {
                var __ret = Internal.Term_0(__Instance);
                return __ret;
            }

            public System.ImeError GetResult(out System.ImeDialogEndStatus result)
            {
                System.ImeDialogEndStatus _result;
                var arg0 = &_result;
                var __ret = Internal.GetResult_0(__Instance, arg0);
                result = _result;
                return __ret;
            }

            public System.ImeDialogStatus Status
            {
                get
                {
                    var __ret = Internal.GetStatus_0(__Instance);
                    return __ret;
                }
            }

            public int UserId
            {
                set
                {
                    var arg0 = value;
                    Internal.SetUserId_0(__Instance, arg0);
                }
            }

            public System.ImeDialogType DialogType
            {
                get
                {
                    var __ret = Internal.GetDialogType_0(__Instance);
                    return __ret;
                }

                set
                {
                    var arg0 = value;
                    Internal.SetDialogType_0(__Instance, arg0);
                }
            }

            public System.ImeLanguage SupportedLanguages
            {
                get
                {
                    var __ret = Internal.GetSupportedLanguages_0(__Instance);
                    return __ret;
                }

                set
                {
                    var arg0 = value;
                    Internal.SetSupportedLanguages_0(__Instance, arg0);
                }
            }

            public System.ImeEnterLabel EnterLabel
            {
                get
                {
                    var __ret = Internal.GetEnterLabel_0(__Instance);
                    return __ret;
                }

                set
                {
                    var arg0 = value;
                    Internal.SetEnterLabel_0(__Instance, arg0);
                }
            }

            public System.ImeOption Options
            {
                get
                {
                    var __ret = Internal.GetOptions_0(__Instance);
                    return __ret;
                }

                set
                {
                    var arg0 = value;
                    Internal.SetOptions_0(__Instance, arg0);
                }
            }

            public uint MaxTextLength
            {
                get
                {
                    var __ret = Internal.GetMaxTextLength_0(__Instance);
                    return __ret;
                }

                set
                {
                    var arg0 = value;
                    Internal.SetMaxTextLength_0(__Instance, arg0);
                }
            }

            public float PositionX
            {
                get
                {
                    var __ret = Internal.GetPositionX_0(__Instance);
                    return __ret;
                }

                set
                {
                    Internal.SetPositionX_0(__Instance, value);
                }
            }

            public float PositionY
            {
                get
                {
                    var __ret = Internal.GetPositionY_0(__Instance);
                    return __ret;
                }

                set
                {
                    Internal.SetPositionY_0(__Instance, value);
                }
            }

            public System.ImeHorizontalAlignment HorizontalAlignment
            {
                get
                {
                    var __ret = Internal.GetHorizontalAlignment_0(__Instance);
                    return __ret;
                }

                set
                {
                    var arg0 = value;
                    Internal.SetHorizontalAlignment_0(__Instance, arg0);
                }
            }

            public System.ImeVerticalAlignment VerticalAlignment
            {
                get
                {
                    var __ret = Internal.GetVerticalAlignment_0(__Instance);
                    return __ret;
                }

                set
                {
                    var arg0 = value;
                    Internal.SetVerticalAlignment_0(__Instance, arg0);
                }
            }

            public string Placeholder
            {
                get
                {
                    var __ret = Internal.GetPlaceholder_0(__Instance);
                    if (__ret == global::System.IntPtr.Zero) return null;
                    return Marshal.PtrToStringAnsi(__ret);
                }

                set
                {
                    var arg0 = Marshal.StringToHGlobalAnsi(value);
                    Internal.SetPlaceholder_0(__Instance, arg0);
                    Marshal.FreeHGlobal(arg0);
                }
            }

            public string Title
            {
                get
                {
                    var __ret = Internal.GetTitle_0(__Instance);
                    if (__ret == global::System.IntPtr.Zero) return null;
                    return Marshal.PtrToStringAnsi(__ret);
                }

                set
                {
                    var arg0 = Marshal.StringToHGlobalAnsi(value);
                    Internal.SetTitle_0(__Instance, arg0);
                    Marshal.FreeHGlobal(arg0);
                }
            }

            public string InputText
            {
                get
                {
                    var __ret = Internal.GetInputText_0(__Instance);
                    if (__ret == global::System.IntPtr.Zero) return null;
                    return Marshal.PtrToStringAnsi(__ret);
                }

                set
                {
                    var arg0 = Marshal.StringToHGlobalAnsi(value);
                    Internal.SetInputText_0(__Instance, arg0);
                    Marshal.FreeHGlobal(arg0);
                }
            }
        }
    }
}
