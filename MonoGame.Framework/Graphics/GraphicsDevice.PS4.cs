// MonoGame - Copyright (C) The MonoGame Team
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Sce.PlayStation4.Graphics;
using Sce.PlayStation4.System;

namespace Microsoft.Xna.Framework.Graphics
{
    public partial class GraphicsDevice
    {
        internal GraphicsSystem _system;

        private readonly Dictionary<int, DynamicVertexBuffer> _userVertexBuffers = new Dictionary<int, DynamicVertexBuffer>();
        private DynamicIndexBuffer _userIndexBuffer16;
        private DynamicIndexBuffer _userIndexBuffer32;

        private readonly Dictionary<ulong, FetchShader> _fetchShaders = new Dictionary<ulong, FetchShader>();

        private void PlatformSetup()
        {
            MaxTextureSlots = 16;
            _system = new GraphicsSystem();
            SpriteBatch.NeedsHalfPixelOffset = true;
        }

        private void PlatformInitialize()
        {
            var is4K = PresentationParameters.BackBufferWidth == 3840 && PresentationParameters.BackBufferHeight == 2160;
            var is1080 = PresentationParameters.BackBufferWidth == 1920 && PresentationParameters.BackBufferHeight == 1080;
            var is720 = PresentationParameters.BackBufferWidth == 1280 && PresentationParameters.BackBufferHeight == 720;

            var mode = SystemService.RenderingMode;
            switch (mode)
            {
                case SystemServiceRenderingMode.NeoHighResolution:
                    if (!is4K)
                        throw new NotSupportedException("The back buffer resolution must be 3840x2160.");
                    break;
                case SystemServiceRenderingMode.NeoFullHD:
                    if (!is1080)
                        throw new NotSupportedException("The back buffer resolution must be 1920x1080.");
                    break;
                case SystemServiceRenderingMode.NeoEnhancedFullHD:
                    if (!is4K && !is1080)
                        throw new NotSupportedException("The back buffer resolution must be 3840x2160 or 1920x1080.");
                    break;
                case SystemServiceRenderingMode.Base:
                default:
                    if (!is1080 && !is720)
                        throw new NotSupportedException("The back buffer resolution must be 1920x1080 or 1280x720.");
                    break;
            }

            _system.Initialize( PresentationParameters.BackBufferWidth, 
                                PresentationParameters.BackBufferHeight, 
                                (TextureFormat)PresentationParameters.BackBufferFormat,
                                (Sce.PlayStation4.Graphics.DepthFormat)PresentationParameters.DepthStencilFormat);
            _viewport = new Viewport(0, 0, PresentationParameters.BackBufferWidth, PresentationParameters.BackBufferHeight);
        }

        private void PlatformClear(ClearOptions options, Vector4 color, float depth, int stencil)
        {
            _system.Clear((Sce.PlayStation4.Graphics.ClearOptions)options, color.X, color.Y, color.Z, color.W, depth, stencil);

            // Clear clobbers a bunch of state, so just make it 
            // all dirty and it will get re-applied on the next draw.
            PlatformSetViewport(ref _viewport);
            _depthStencilStateDirty = true;
            _blendStateDirty = true;
            _pixelShaderDirty = true;
            _vertexShaderDirty = true;
            _rasterizerStateDirty = true;
            _scissorRectangleDirty = true;
        }

        internal void PlatformSetDirty()
        {
            PlatformSetViewport(ref _viewport);
            _depthStencilStateDirty = true;
            _blendStateDirty = true;
            _pixelShaderDirty = true;
            _vertexShaderDirty = true;
            _rasterizerStateDirty = true;
            _scissorRectangleDirty = true;
        }

        private void PlatformDispose()
        {
            if (_userIndexBuffer16 != null)
            {
                _userIndexBuffer16.Dispose();
                _userIndexBuffer16 = null;
            }
            if (_userIndexBuffer32 != null)
            {
                _userIndexBuffer32.Dispose();
                _userIndexBuffer32 = null;
            }

            foreach (var vb in _userVertexBuffers.Values)
                vb.Dispose();
            _userVertexBuffers.Clear();

            foreach (var fetch in _fetchShaders)
                fetch.Value.Dispose();
            _fetchShaders.Clear();

            _system.Dispose();
            _system = null;
        }

        private void PlatformPresent()
        {
            _system.Present();
            
            // Restore the viewport after present.
            _viewport = new Viewport(0, 0, PresentationParameters.BackBufferWidth, PresentationParameters.BackBufferHeight);

            // Reapply all the render states.
            Textures.Dirty();
            SamplerStates.Dirty();
            _depthStencilStateDirty = true;
            _blendStateDirty = true;
            _indexBufferDirty = true;
            _vertexBufferDirty = true;
            _pixelShaderDirty = true;
            _vertexShaderDirty = true;
            _rasterizerStateDirty = true;
            _scissorRectangleDirty = true;
        }

        private void PlatformSetViewport(ref Viewport viewport)
        {
            _system.SetViewport(viewport.X, viewport.Y, viewport.Width, viewport.Height, viewport.MinDepth, viewport.MaxDepth);
        }

        private void PlatformApplyDefaultRenderTarget()
        {
            _system.SetRenderTargets(null, null, null, null);
        }

        internal void PlatformResolveRenderTargets()
        {
            // Resolving MSAA render targets should be done here.
        }

        private IRenderTarget PlatformApplyRenderTargets()
        {
            Textures.ClearTargets(this, _currentRenderTargetBindings);

            var target0 = _currentRenderTargetBindings[0].RenderTarget as RenderTarget2D;
            var target1 = _currentRenderTargetBindings[1].RenderTarget as RenderTarget2D;
            var target2 = _currentRenderTargetBindings[2].RenderTarget as RenderTarget2D;
            var target3 = _currentRenderTargetBindings[3].RenderTarget as RenderTarget2D;
            _system.SetRenderTargets(target0._texture as RenderTarget,
                                    target1 != null ? target1._texture as RenderTarget : null,
                                    target2 != null ? target2._texture as RenderTarget : null,
                                    target3 != null ? target3._texture as RenderTarget : null);

            return target0;
        }

        private FetchShader GetFetchShader(Shader shader, VertexDeclaration decl)
        {
            FetchShader fetch;

            // Lookup the fetch shader using the shader and declaration as the key.
            var key = (ulong)decl.HashKey << 32 | (uint)shader.HashKey;
            if (!_fetchShaders.TryGetValue(key, out fetch))
            {
                var remap = shader.GenerateFetchRemap(decl);
                unsafe
                {
                    fixed (uint* ptr = remap)
                    {
                        fetch = new FetchShader(shader._vertexShader, ptr, remap.Length);
                    }
                }
                _fetchShaders.Add(key, fetch);
            }

            return fetch;
        }

        internal void PlatformApplyState(bool applyShaders)
        {
            if (_scissorRectangleDirty)
            {
                _system.SetScissorRectangle(_scissorRectangle.Left, _scissorRectangle.Top,
                                            _scissorRectangle.Right, _scissorRectangle.Bottom);
                _scissorRectangleDirty = false;
            }
            if (_blendStateDirty)
            {
                _blendState.PlatformApplyState(this);
                _blendStateDirty = false;
            }
            if (_depthStencilStateDirty)
            {
                _depthStencilState.PlatformApplyState(this);
                _depthStencilStateDirty = false;
            }
            if (_rasterizerStateDirty)
            {
                _rasterizerState.PlatformApplyState(this);
                _rasterizerStateDirty = false;
            }

            // If we're not applying shaders then early out now.
            if (!applyShaders)
                return;

            if (_vertexBufferDirty)
            {
                if (_vertexBuffer != null)
                    _system.VertexBuffer = _vertexBuffer._buffer;
            }

            if (_indexBufferDirty)
            {
                if (_indexBuffer != null)
                    _system.IndexBuffer = _indexBuffer._buffer;
                _indexBufferDirty = false;
            }

            if (_vertexShader == null)
                throw new InvalidOperationException("A vertex shader must be set!");
            if (_pixelShader == null)
                throw new InvalidOperationException("A pixel shader must be set!");

            if (_vertexShaderDirty || _vertexBufferDirty)
            {
                var fetch = GetFetchShader(_vertexShader, _vertexBuffer.VertexDeclaration);
                _system.SetVertexShader(_vertexShader._vertexShader, fetch);
                _vertexShaderDirty = _vertexBufferDirty = false;
            }

            if (_pixelShaderDirty)
            {
                _system.PixelShader = _pixelShader._pixelShader;
                _pixelShaderDirty = false;
            }

            _vertexConstantBuffers.SetConstantBuffers(this);
            _pixelConstantBuffers.SetConstantBuffers(this);

            Textures.SetTextures(this);
            SamplerStates.PlatformSetSamplers(this);
        }

        private void PlatformDrawIndexedPrimitives(PrimitiveType primitiveType, int baseVertex, int startIndex, int primitiveCount)
        {
            PlatformApplyState(true);
            _system.DrawIndexedPrimitives((Sce.PlayStation4.Graphics.PrimitiveType)primitiveType, baseVertex, startIndex, primitiveCount);
        }

        private void PlatformDrawPrimitives(PrimitiveType primitiveType, int vertexStart, int vertexCount)
        {
            PlatformApplyState(true);
            _system.DrawPrimitives((Sce.PlayStation4.Graphics.PrimitiveType)primitiveType, vertexStart, vertexCount);
        }

        private int SetUserVertexBuffer<T>(T[] vertexData, int vertexOffset, int vertexCount, VertexDeclaration vertexDecl)
            where T : struct
        {
            DynamicVertexBuffer buffer;

            if (!_userVertexBuffers.TryGetValue(vertexDecl.HashKey, out buffer) || buffer.VertexCount < vertexCount)
            {
                // Dispose the previous buffer if we have one.
                if (buffer != null)
                    buffer.Dispose();

                buffer = new DynamicVertexBuffer(this, vertexDecl, Math.Max(vertexCount, 2000), BufferUsage.WriteOnly);
                _userVertexBuffers[vertexDecl.HashKey] = buffer;
            }

            var startVertex = buffer.UserOffset;


            if ((vertexCount + buffer.UserOffset) < buffer.VertexCount)
            {
                buffer.UserOffset += vertexCount;
                buffer.SetData(startVertex * vertexDecl.VertexStride, vertexData, vertexOffset, vertexCount, vertexDecl.VertexStride, SetDataOptions.NoOverwrite);
            }
            else
            {
                buffer.UserOffset = vertexCount;
                buffer.SetData(vertexData, vertexOffset, vertexCount, SetDataOptions.Discard);
                startVertex = 0;
            }

            SetVertexBuffer(buffer);

            return startVertex;
        }

        private int SetUserIndexBuffer<T>(T[] indexData, int indexOffset, int indexCount)
            where T : struct
        {
            DynamicIndexBuffer buffer;

            var indexType = typeof(T);
            var indexSize = Marshal.SizeOf(indexType);
            var indexElementSize = indexSize == 2 ? IndexElementSize.SixteenBits : IndexElementSize.ThirtyTwoBits;

            var requiredIndexCount = Math.Max(indexCount, 6000);
            if (indexElementSize == IndexElementSize.SixteenBits)
            {
                if (_userIndexBuffer16 == null || _userIndexBuffer16.IndexCount < requiredIndexCount)
                {
                    if (_userIndexBuffer16 != null)
                        _userIndexBuffer16.Dispose();

                    _userIndexBuffer16 = new DynamicIndexBuffer(this, indexElementSize, requiredIndexCount, BufferUsage.WriteOnly);
                }

                buffer = _userIndexBuffer16;
            }
            else
            {
                if (_userIndexBuffer32 == null || _userIndexBuffer32.IndexCount < requiredIndexCount)
                {
                    if (_userIndexBuffer32 != null)
                        _userIndexBuffer32.Dispose();

                    _userIndexBuffer32 = new DynamicIndexBuffer(this, indexElementSize, requiredIndexCount, BufferUsage.WriteOnly);
                }

                buffer = _userIndexBuffer32;
            }

            var startIndex = buffer.UserOffset;

            if ((indexCount + buffer.UserOffset) < buffer.IndexCount)
            {
                buffer.UserOffset += indexCount;
                buffer.SetData(startIndex * indexSize, indexData, indexOffset, indexCount, SetDataOptions.NoOverwrite);
            }
            else
            {
                startIndex = 0;
                buffer.UserOffset = indexCount;
                buffer.SetData(indexData, indexOffset, indexCount, SetDataOptions.Discard);
            }

            Indices = buffer;

            return startIndex;
        }

        private void PlatformDrawUserPrimitives<T>(PrimitiveType primitiveType, T[] vertexData, int vertexOffset, VertexDeclaration vertexDeclaration, int vertexCount) where T : struct
        {
            var startVertex = SetUserVertexBuffer(vertexData, vertexOffset, vertexCount, vertexDeclaration);

            PlatformApplyState(true);

            _system.DrawPrimitives((Sce.PlayStation4.Graphics.PrimitiveType)primitiveType, startVertex, vertexCount);
        }

        private void PlatformDrawUserIndexedPrimitives<T>(PrimitiveType primitiveType, T[] vertexData, int vertexOffset, int numVertices, short[] indexData, int indexOffset, int primitiveCount, VertexDeclaration vertexDeclaration) where T : struct
        {
            var indexCount = GetElementCountArray(primitiveType, primitiveCount);
            var startVertex = SetUserVertexBuffer(vertexData, vertexOffset, numVertices, vertexDeclaration);
            var startIndex = SetUserIndexBuffer(indexData, indexOffset, indexCount);

            PlatformApplyState(true);

            _system.DrawIndexedPrimitives((Sce.PlayStation4.Graphics.PrimitiveType)primitiveType, startVertex, startIndex, primitiveCount);
        }

        private void PlatformDrawUserIndexedPrimitives<T>(PrimitiveType primitiveType, T[] vertexData, int vertexOffset, int numVertices, int[] indexData, int indexOffset, int primitiveCount, VertexDeclaration vertexDeclaration) where T : struct, IVertexType
        {
            var indexCount = GetElementCountArray(primitiveType, primitiveCount);
            var startVertex = SetUserVertexBuffer(vertexData, vertexOffset, numVertices, vertexDeclaration);
            var startIndex = SetUserIndexBuffer(indexData, indexOffset, indexCount);

            PlatformApplyState(true);

            _system.DrawIndexedPrimitives((Sce.PlayStation4.Graphics.PrimitiveType)primitiveType, startVertex, startIndex, primitiveCount);
        }

        private void PlatformDrawUserIndexedPrimitives<T>(PrimitiveType primitiveType, T[] vertexData, int vertexOffset, int numVertices, IndexBuffer indexBuffer, int indexOffset, int primitiveCount, VertexDeclaration vertexDeclaration) where T : struct
        {
            var indexCount = GetElementCountArray(primitiveType, primitiveCount);
            var startVertex = SetUserVertexBuffer(vertexData, vertexOffset, numVertices, vertexDeclaration);

            Indices = indexBuffer;

            PlatformApplyState(true);

            _system.DrawIndexedPrimitives((Sce.PlayStation4.Graphics.PrimitiveType)primitiveType, startVertex, indexOffset, primitiveCount);
        }

        private static GraphicsProfile PlatformGetHighestSupportedGraphicsProfile(GraphicsDevice graphicsDevice)
        {
            return GraphicsProfile.HiDef;
        }
    }
}
