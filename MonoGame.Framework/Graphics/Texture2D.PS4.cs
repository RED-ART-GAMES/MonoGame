// MonoGame - Copyright (C) The MonoGame Team
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.

using System;
using System.IO;
using System.Runtime.InteropServices;
using PS4Texture = Sce.PlayStation4.Graphics.Texture;
using PS4TextureFormat = Sce.PlayStation4.Graphics.TextureFormat;

namespace Microsoft.Xna.Framework.Graphics
{
    public partial class Texture2D
    {
        private Texture2D(GraphicsDevice graphicsDevice, int width, int height, PS4Texture texture)
        {
            GraphicsDevice = graphicsDevice;
            this.width = width;
            this.height = height;
            TexelWidth = 1f / (float)width;
            TexelHeight = 1f / (float)height;
            _format = SurfaceFormat.Color;
            _levelCount = 1;
            _texture = texture;
        }

        protected void PlatformConstruct(int width, int height, bool mipmap, SurfaceFormat format, SurfaceType type, bool shared)
        {
            if (type != SurfaceType.Texture)
                return;

            _texture = new PS4Texture(GraphicsDevice._system);
            _texture.Init2D((PS4TextureFormat)format, width, height, (mipmap ? _levelCount : 1));
        }

        protected void PlatformSetData<T>(int level, Rectangle? rect, T[] data, int startIndex, int elementCount)
        {
            var dataHandle = GCHandle.Alloc(data, GCHandleType.Pinned);

            var elementSizeInByte = Marshal.SizeOf(typeof(T));
            var startBytes = startIndex * elementSizeInByte;
            var dataPtr = (IntPtr)(dataHandle.AddrOfPinnedObject().ToInt64() + startBytes);

            if (rect.HasValue)
            {
                throw new NotImplementedException();
            }
            else
            {
                unsafe
                {
                    _texture.SetData((uint)level, (byte*)dataPtr, 0, (uint)(elementSizeInByte * elementCount));
                }
            }

            dataHandle.Free();
        }

        protected void PlatformGetData<T>(int level, Rectangle? rect, T[] data, int startIndex, int elementCount)
        {
            var dataHandle = GCHandle.Alloc(data, GCHandleType.Pinned);

            var elementSizeInByte = Marshal.SizeOf(typeof(T));
            var startBytes = startIndex * elementSizeInByte;
            var dataPtr = (IntPtr)(dataHandle.AddrOfPinnedObject().ToInt64() + startBytes);

            if (rect.HasValue)
            {
                throw new NotImplementedException();
            }
            else
            {
                unsafe
                {
                    _texture.GetData((uint)level, (byte*)dataPtr, 0, (uint)(elementSizeInByte * elementCount));
                }
            }

            dataHandle.Free();
        }

        private static unsafe Texture2D PlatformFromStream(GraphicsDevice graphicsDevice, Stream stream)
        {
            // Read it all into memory!
            var dataLength = (int)stream.Length;
            var streamTemp = new byte[dataLength];
            stream.Read(streamTemp, 0, dataLength);

            var handle = GCHandle.Alloc(streamTemp, GCHandleType.Pinned);

            int width, height;
            var texture = new PS4Texture(graphicsDevice._system);

            try
            {
                unsafe
                {
                    // Pass it to the native to initialize the texture.
                    if (!texture.Init2DFromStream((byte*)handle.AddrOfPinnedObject(), (uint)dataLength, out width, out height))
                    {
                        texture.Dispose();
                        throw new InvalidOperationException("File corrupt or format not supported.");
                    }                        
                }
            }
            finally
            {
                handle.Free();
            }

            // Create the texture.
            return new Texture2D(graphicsDevice, width, height, texture);
        }

        private void PlatformSaveAsJpeg(Stream stream, int width, int height)
        {
            throw new NotImplementedException();
        }

        private void PlatformSaveAsPng(Stream stream, int width, int height)
        {
            throw new NotImplementedException();
        }

        private void PlatformReload(Stream textureStream)
        {
            throw new NotImplementedException();
        }
    }
}
