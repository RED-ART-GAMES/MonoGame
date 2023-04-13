//----------------------------------------------------------------------------
// This is autogenerated code by CppSharp.
// Do not edit this file or all your changes will be lost after re-generation.
//----------------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Security;

namespace Sce.PlayStation4
{
    namespace Graphics
    {
        public enum PngReaderResult
        {
            OK = 0,
            InvalidAddr = -2140602367,
            InvalidSize = -2140602366,
            InvalidParam = -2140602365,
            InvalidHandle = -2140602364,
            InvalidWorkMemory = -2140602363,
            InvalidData = -2140602352,
            UnsupportedData = -2140602351,
            DecodeError = -2140602350,
            Fatal = -2140602336
        }

        public unsafe partial class PngReader : IDisposable
        {
            [StructLayout(LayoutKind.Explicit, Size = 48)]
            public partial struct Internal
            {
                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics9PngReaderC2ERKS0_")]
                internal static extern void cctor_0(global::System.IntPtr instance, global::System.IntPtr _0);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics9PngReaderC2Ev")]
                internal static extern void ctor_1(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics9PngReaderD2Ev")]
                internal static extern void dtor_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics9PngReader10InitializeEi")]
                internal static extern Graphics.PngReaderResult Initialize_0(global::System.IntPtr instance, int maxImageWidth);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics9PngReader14LoadCompressedEPKhi")]
                internal static extern Graphics.PngReaderResult LoadCompressed_0(global::System.IntPtr instance, byte* compressed, int size);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics9PngReader18OutputUncompressedEPhi")]
                internal static extern Graphics.PngReaderResult OutputUncompressed_0(global::System.IntPtr instance, byte* buffer, int size);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics9PngReader7CleanupEv")]
                internal static extern void Cleanup_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZNK8Graphics9PngReader13GetOutputSizeEv")]
                internal static extern int GetOutputSize_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZNK8Graphics9PngReader8GetWidthEv")]
                internal static extern int GetWidth_0(global::System.IntPtr instance);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZNK8Graphics9PngReader9GetHeightEv")]
                internal static extern int GetHeight_0(global::System.IntPtr instance);
            }

            public global::System.IntPtr __Instance { get; protected set; }

            internal PngReader(PngReader.Internal* native)
                : this(new global::System.IntPtr(native))
            {
            }

            internal PngReader(PngReader.Internal native)
                : this(&native)
            {
            }

            public PngReader(global::System.IntPtr native, bool isInternalImpl = false)
            {
                __Instance = native;
            }

            public PngReader()
            {
                __Instance = Marshal.AllocHGlobal(48);
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

            public Graphics.PngReaderResult Initialize(int maxImageWidth)
            {
                var __ret = Internal.Initialize_0(__Instance, maxImageWidth);
                return __ret;
            }

            public Graphics.PngReaderResult LoadCompressed(byte* compressed, int size)
            {
                var arg0 = compressed;
                var __ret = Internal.LoadCompressed_0(__Instance, arg0, size);
                return __ret;
            }

            public Graphics.PngReaderResult OutputUncompressed(byte* buffer, int size)
            {
                var arg0 = buffer;
                var __ret = Internal.OutputUncompressed_0(__Instance, arg0, size);
                return __ret;
            }

            public void Cleanup()
            {
                Internal.Cleanup_0(__Instance);
            }

            public int OutputSize
            {
                get
                {
                    var __ret = Internal.GetOutputSize_0(__Instance);
                    return __ret;
                }
            }

            public int Width
            {
                get
                {
                    var __ret = Internal.GetWidth_0(__Instance);
                    return __ret;
                }
            }

            public int Height
            {
                get
                {
                    var __ret = Internal.GetHeight_0(__Instance);
                    return __ret;
                }
            }
        }
    }
}
