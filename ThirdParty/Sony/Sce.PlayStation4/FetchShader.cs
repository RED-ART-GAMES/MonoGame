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
        public unsafe partial class FetchShader : IDisposable
        {
            [StructLayout(LayoutKind.Explicit, Size = 24)]
            public partial struct Internal
            {
                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics11FetchShaderC2EPNS_12VertexShaderEPKji")]
                internal static extern void ctor_0(global::System.IntPtr instance, global::System.IntPtr shader, uint* remap, int count);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics11FetchShaderC2ERKS0_")]
                internal static extern void cctor_1(global::System.IntPtr instance, global::System.IntPtr _0);

                [SuppressUnmanagedCodeSecurity]
                [DllImport("scePlayStation4.prx", CallingConvention = global::System.Runtime.InteropServices.CallingConvention.Cdecl,
                    EntryPoint="_ZN8Graphics11FetchShaderD2Ev")]
                internal static extern void dtor_0(global::System.IntPtr instance);
            }

            public global::System.IntPtr __Instance { get; protected set; }

            internal FetchShader(FetchShader.Internal* native)
                : this(new global::System.IntPtr(native))
            {
            }

            internal FetchShader(FetchShader.Internal native)
                : this(&native)
            {
            }

            public FetchShader(global::System.IntPtr native, bool isInternalImpl = false)
            {
                __Instance = native;
            }

            public FetchShader(Graphics.VertexShader shader, uint* remap, int count)
            {
                __Instance = Marshal.AllocHGlobal(24);
                var arg0 = shader == (Graphics.VertexShader) null ? global::System.IntPtr.Zero : shader.__Instance;
                var arg1 = remap;
                var arg2 = count;
                Internal.ctor_0(__Instance, arg0, arg1, arg2);
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
        }
    }
}