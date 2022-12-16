// MonoGame - Copyright (C) The MonoGame Team
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.

using System;
using System.Runtime.InteropServices;
using Sce.PlayStation4.Graphics;
using PSIndexBuffer = Sce.PlayStation4.Graphics.IndexBuffer;

namespace Microsoft.Xna.Framework.Graphics
{
    public partial class IndexBuffer
    {
        internal PSIndexBuffer _buffer;

        private void PlatformConstruct(IndexElementSize indexElementSize, int indexCount)
        {
            _buffer = new PSIndexBuffer(GraphicsDevice._system, (IndexElement)IndexElementSize, indexCount);
        }

        private void PlatformGraphicsDeviceResetting()
        {
            throw new NotSupportedException();
        }

        private void PlatformGetData<T>(int offsetInBytes, T[] data, int startIndex, int elementCount) where T : struct
        {
            var elementSizeInBytes = Marshal.SizeOf(typeof(T));
            var startBytes = startIndex * elementSizeInBytes;
            var dataHandle = GCHandle.Alloc(data, GCHandleType.Pinned);
            var dataPtr = (IntPtr)(dataHandle.AddrOfPinnedObject().ToInt64() + startBytes);

            unsafe
            {
                _buffer.GetData(offsetInBytes, (byte*)dataPtr, elementCount * elementSizeInBytes);
            }

            dataHandle.Free();
        }

        private void PlatformSetDataInternal<T>(int offsetInBytes, T[] data, int startIndex, int elementCount, SetDataOptions options) where T : struct
        {
            var elementSizeInBytes = Marshal.SizeOf(typeof(T));
            var startBytes = startIndex * elementSizeInBytes;
            var dataBytes = elementCount * elementSizeInBytes;
            var dataHandle = GCHandle.Alloc(data, GCHandleType.Pinned);
            var dataPtr = (IntPtr)(dataHandle.AddrOfPinnedObject().ToInt64() + startBytes);

            // TODO: We need to figure out the correct behavior 
            // for SetDataOptions.None on a dynamic buffer.
            //
            // For now we always discard as it is a pretty safe default.
            //
            var discard =   _isDynamic &&
                            (   options == SetDataOptions.Discard ||
                                options == SetDataOptions.None);

            unsafe
            {
                _buffer.SetData(offsetInBytes, (byte*)dataPtr, dataBytes, discard);
            }

            dataHandle.Free();
        }

        protected override void Dispose(bool disposing)
        {
            if (!IsDisposed && disposing)
            {
                _buffer.Dispose();
                _buffer = null;
            }

            base.Dispose(disposing);
        }
    }
}
