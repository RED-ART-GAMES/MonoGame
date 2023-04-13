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
        public enum VideoRecordingResult
        {
            Ok = 0,
            StatusNone = 0,
            StatusRunning = 1,
            StatusPaused = 2,
            ErrorOutOfMemory = -2136473599,
            ErrorFatal = -2136473598,
            ErrorInvalidValue = -2136473597,
            ErrorFileOpen = -2136473596,
            ErrorFileWrite = -2136473595,
            ErrorInvalidState = -2136473594,
            ErrorInterrupted = -2136473593,
            ErrorNoSpace = -2136473591,
            ErrorFileNoData = -2136473590,
            ErrorStringConversionFailed = -2136473589
        }

        public unsafe static partial class VideoRecording
        {
            [StructLayout(LayoutKind.Explicit, Size = 1)]
            public partial struct Internal
            {
                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording4OpenEPKcNS_10ThreadPrioEl")]
                internal static extern System.VideoRecordingResult Open_0(global::System.IntPtr videoFileName, System.ThreadPrio threadPriority, long bufferSeconds);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording5StartEv")]
                internal static extern System.VideoRecordingResult Start_0();

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording4StopEv")]
                internal static extern System.VideoRecordingResult Stop_0();

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording5CloseEb")]
                internal static extern System.VideoRecordingResult Close_0(bool discardRecording);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording17MarkChapterChangeEv")]
                internal static extern System.VideoRecordingResult MarkChapterChange_0();

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording17ProhibitRecordingEv")]
                internal static extern System.VideoRecordingResult ProhibitRecording_0();

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording11SetSubtitleEPKc")]
                internal static extern System.VideoRecordingResult SetSubtitle_0(global::System.IntPtr value);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording14SetDescriptionEPKc")]
                internal static extern System.VideoRecordingResult SetDescription_0(global::System.IntPtr value);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording11SetCommentsEPKc")]
                internal static extern System.VideoRecordingResult SetComments_0(global::System.IntPtr value);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording11SetKeywordsEPKc")]
                internal static extern System.VideoRecordingResult SetKeywords_0(global::System.IntPtr value);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording12SetCopyrightEPKc")]
                internal static extern System.VideoRecordingResult SetCopyright_0(global::System.IntPtr value);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording18SetPermissionLevelEi")]
                internal static extern System.VideoRecordingResult SetPermissionLevel_0(int permissionLevel);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN6System14VideoRecording9GetStatusEv")]
                internal static extern System.VideoRecordingResult GetStatus_0();
            }

            public static System.VideoRecordingResult Open(string videoFileName, System.ThreadPrio threadPriority, long bufferSeconds)
            {
                var arg0 = Marshal.StringToHGlobalAnsi(videoFileName);
                var arg1 = threadPriority;
                var arg2 = bufferSeconds;
                var __ret = Internal.Open_0(arg0, arg1, arg2);
                Marshal.FreeHGlobal(arg0);
                return __ret;
            }

            public static System.VideoRecordingResult Start()
            {
                var __ret = Internal.Start_0();
                return __ret;
            }

            public static System.VideoRecordingResult Stop()
            {
                var __ret = Internal.Stop_0();
                return __ret;
            }

            public static System.VideoRecordingResult Close(bool discardRecording)
            {
                var __ret = Internal.Close_0(discardRecording);
                return __ret;
            }

            public static System.VideoRecordingResult MarkChapterChange()
            {
                var __ret = Internal.MarkChapterChange_0();
                return __ret;
            }

            public static System.VideoRecordingResult ProhibitRecording()
            {
                var __ret = Internal.ProhibitRecording_0();
                return __ret;
            }

            public static System.VideoRecordingResult SetSubtitle(string value)
            {
                var arg0 = Marshal.StringToHGlobalAnsi(value);
                var __ret = Internal.SetSubtitle_0(arg0);
                Marshal.FreeHGlobal(arg0);
                return __ret;
            }

            public static System.VideoRecordingResult SetDescription(string value)
            {
                var arg0 = Marshal.StringToHGlobalAnsi(value);
                var __ret = Internal.SetDescription_0(arg0);
                Marshal.FreeHGlobal(arg0);
                return __ret;
            }

            public static System.VideoRecordingResult SetComments(string value)
            {
                var arg0 = Marshal.StringToHGlobalAnsi(value);
                var __ret = Internal.SetComments_0(arg0);
                Marshal.FreeHGlobal(arg0);
                return __ret;
            }

            public static System.VideoRecordingResult SetKeywords(string value)
            {
                var arg0 = Marshal.StringToHGlobalAnsi(value);
                var __ret = Internal.SetKeywords_0(arg0);
                Marshal.FreeHGlobal(arg0);
                return __ret;
            }

            public static System.VideoRecordingResult SetCopyright(string value)
            {
                var arg0 = Marshal.StringToHGlobalAnsi(value);
                var __ret = Internal.SetCopyright_0(arg0);
                Marshal.FreeHGlobal(arg0);
                return __ret;
            }

            public static System.VideoRecordingResult SetPermissionLevel(int permissionLevel)
            {
                var arg0 = permissionLevel;
                var __ret = Internal.SetPermissionLevel_0(arg0);
                return __ret;
            }

            public static System.VideoRecordingResult Status
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
