#include "Texture.h"
#include "renderTarget.h"

#include "graphicsSystem.h"
#include "graphicsHelpers.h"
#include "../allocator.h"

#include <sdk_version.h>
#include <gnm.h>
#include <assert.h>
#include <math.h>

using namespace Graphics;


Texture::Texture(GraphicsSystem *system)
{ 
	assert(system != nullptr);

	_system = system;
	_texture = nullptr;
	_isTarget = false; 
	_ownsTexture = true; 
}

Texture::~Texture()
{
	if (!_ownsTexture)
		return;

	_system->_safeDeleteBuffer(_texture->getBaseAddress());
	delete _texture;
}

void Texture::Init2D(TextureFormat format, int32_t width, int32_t height, int32_t mips)
{
	assert(mips >= 1);
	assert(_texture == nullptr);

	auto texture = new sce::Gnm::Texture();
	_texture = texture;

	// BCn compressed textures come through the pipeline as
	// tiled data, otherwise use linear for flexibility.
	Gnm::TileMode tileMode;
	switch(format)
	{
	case TextureFormat::TextureFormat_PlayStation4_BC1Unorm:
	case TextureFormat::TextureFormat_PlayStation4_BC2Unorm:
	case TextureFormat::TextureFormat_PlayStation4_BC3Unorm:
		tileMode = Gnm::kTileModeThin_1dThin;
		break;

	default:
		tileMode = Gnm::kTileModeDisplay_LinearAligned;
	}

#if SCE_ORBIS_SDK_VERSION >= 0x05008041u // SDK Version 5.0

	Gnm::TextureSpec spec;
	spec.init();
	spec.m_textureType = Gnm::TextureType::kTextureType2d;
	spec.m_format = ToDataFormat(format);
	spec.m_width = width;
	spec.m_height = height;
	spec.m_depth = 1;
	spec.m_numMipLevels = mips;
	spec.m_tileModeHint = tileMode;
	spec.m_numFragments = Gnm::kNumFragments1;
	spec.m_minGpuMode = Gnm::getGpuMode();
	spec.m_numSlices = 1;
	spec.m_pitch = 0;
	//spec.m_flags = ???
	auto err = texture->init(&spec);
	SCE_GNM_ASSERT(err == SCE_GNM_OK);

	auto textureSizeAlign = texture->getSizeAlign();

#else

	auto textureSizeAlign = texture->initAs2d(
		width, height, mips,
		ToDataFormat(format),
		tileMode,
#if SCE_ORBIS_SDK_VERSION >= 0x02000071u // SDK Version 2.0
		Gnm::kNumFragments1);
#else
		Gnm::kNumSamples1);
#endif

#endif

	// Allocate the texture data using the alignment returned by initAs2d
	void *textureData = mem::allocShared(textureSizeAlign);
	texture->setBaseAddress(textureData);
}

void Texture::Init3D(TextureFormat format, int32_t width, int32_t height, int32_t depth, int32_t mips)
{
	assert(mips >= 1);
	assert(_texture == nullptr);

	auto texture = new sce::Gnm::Texture();
	_texture = texture;

	// BCn compressed textures come through the pipeline as
	// tiled data, otherwise use linear for flexibility.
	Gnm::TileMode tileMode;
	switch(format)
	{
	case TextureFormat::TextureFormat_PlayStation4_BC1Unorm:
	case TextureFormat::TextureFormat_PlayStation4_BC2Unorm:
	case TextureFormat::TextureFormat_PlayStation4_BC3Unorm:
		tileMode = Gnm::kTileModeThin_1dThin;
		break;

	default:
		tileMode = Gnm::kTileModeDisplay_LinearAligned;
	}

#if SCE_ORBIS_SDK_VERSION >= 0x05008041u // SDK Version 5.0

	Gnm::TextureSpec spec;
	spec.init();
	spec.m_textureType = Gnm::TextureType::kTextureType3d;
	spec.m_format = ToDataFormat(format);
	spec.m_width = width;
	spec.m_height = height;
	spec.m_depth = depth;
	spec.m_numMipLevels = mips;
	spec.m_tileModeHint = tileMode;
	spec.m_numFragments = Gnm::kNumFragments1;
	spec.m_minGpuMode = Gnm::getGpuMode();
	spec.m_numSlices = 1;
	spec.m_pitch = 0;
	//spec.m_flags = ???
	auto err = texture->init(&spec);
	SCE_GNM_ASSERT(err == SCE_GNM_OK);

	auto textureSizeAlign = texture->getSizeAlign();

#else

	auto textureSizeAlign = texture->initAs3d(
		width, height, depth, mips,
		ToDataFormat(format),
		tileMode);

#endif

	// Allocate the texture data using the alignment returned by initAs3d
	void *textureData = mem::allocShared(textureSizeAlign);
	texture->setBaseAddress(textureData);
}

void Texture::InitCube(TextureFormat format, int32_t width, int32_t height, int32_t mips)
{
	assert(mips >= 1);
	assert(_texture == nullptr);

	auto texture = new sce::Gnm::Texture();
	_texture = texture;

	// BCn compressed textures come through the pipeline as
	// tiled data, otherwise use linear for flexibility.
	Gnm::TileMode tileMode;
	switch(format)
	{
	case TextureFormat::TextureFormat_PlayStation4_BC1Unorm:
	case TextureFormat::TextureFormat_PlayStation4_BC2Unorm:
	case TextureFormat::TextureFormat_PlayStation4_BC3Unorm:
		tileMode = Gnm::kTileModeThin_1dThin;
		break;

	default:
		tileMode = Gnm::kTileModeDisplay_LinearAligned;
	}

#if SCE_ORBIS_SDK_VERSION >= 0x05008041u // SDK Version 5.0

	Gnm::TextureSpec spec;
	spec.init();
	spec.m_textureType = Gnm::TextureType::kTextureTypeCubemap;
	spec.m_format = ToDataFormat(format);
	spec.m_width = width;
	spec.m_height = height;
	spec.m_depth = 1;
	spec.m_numMipLevels = mips;
	spec.m_tileModeHint = tileMode;
	spec.m_numFragments = Gnm::kNumFragments1;
	spec.m_minGpuMode = Gnm::getGpuMode();
	spec.m_numSlices = 1;
	spec.m_pitch = 0;
	//spec.m_flags = ???
	auto err = texture->init(&spec);
	SCE_GNM_ASSERT(err == SCE_GNM_OK);

	auto textureSizeAlign = texture->getSizeAlign();

#else

	auto textureSizeAlign = texture->initAsCubemap(
		width, height, mips,
		ToDataFormat(format),
		tileMode);

#endif

	// Allocate the texture data using the alignment returned by initAsCubemap
	void *textureData = mem::allocShared(textureSizeAlign);
	texture->setBaseAddress(textureData);
}

void Texture::SetData(uint32_t mipLevel, uint8_t* data, uint32_t offset, uint32_t length)
{
	auto width = MAX(1, _texture->getWidth() >> mipLevel);
	auto height = MAX(1, _texture->getHeight() >> mipLevel);
	//auto depth = MAX(1, _texture->getDepth() >> mipLevel);
	auto pixelBits = _texture->getDataFormat().getBitsPerElement();

	uint64_t levelOffset, levelSize;
	GpuAddress::computeTextureSurfaceOffsetAndSize(&levelOffset, &levelSize, _texture, mipLevel, 0);

	auto baseAddr = (unsigned char*)_texture->getBaseAddress();
	baseAddr += levelOffset;

	if (offset == 0 && length == levelSize)
		memcpy(baseAddr, data, length);
	else
	{
		GpuAddress::TilingParameters tile;
		tile.initFromTexture(_texture, mipLevel, 0);
		GpuAddress::SurfaceInfo info;
		GpuAddress::computeSurfaceInfo(&info, &tile);

		auto pitch = info.m_pitch;
		auto dataPitchBytes = (width * pixelBits) / 8;
		auto texPitchBytes = (pitch * pixelBits) / 8;

		for (auto h=0; h < height; h++)
		{
			memcpy(baseAddr, data, MIN(dataPitchBytes, length));

			// Have we copied all the data we got?
			length -= dataPitchBytes;
			if (length <= 0)
				break;

			data += dataPitchBytes;
			baseAddr += texPitchBytes;
		}
	}
}

void Texture::GetData(uint32_t mipLevel, uint8_t* data, uint32_t offset, uint32_t length)
{
	auto width = MAX(1, _texture->getWidth() >> mipLevel);
	auto height = MAX(1, _texture->getHeight() >> mipLevel);
	//auto depth = MAX(1, _texture->getDepth() >> mipLevel);
	auto pixelBits = _texture->getDataFormat().getBitsPerElement();

	uint64_t levelOffset, levelSize;
	unsigned char* baseAddr;

	if (_isTarget)	
	{
		auto target = (RenderTarget*)this;
		baseAddr = target->GetDataDetiled(&levelOffset, &levelSize, mipLevel);
	}
	else
	{
		GpuAddress::computeTextureSurfaceOffsetAndSize(&levelOffset, &levelSize, _texture, mipLevel, 0);
		baseAddr = (unsigned char*)_texture->getBaseAddress();
		baseAddr += levelOffset;
	}

	if (offset == 0 && length == levelSize)
		memcpy(data, baseAddr, length);
	else
	{
		GpuAddress::TilingParameters tile;
		tile.initFromTexture(_texture, mipLevel, 0);
		GpuAddress::SurfaceInfo info;
		GpuAddress::computeSurfaceInfo(&info, &tile);

		auto pitch = info.m_pitch;
		auto texPitchBytes = (pitch * pixelBits) / 8;
		auto dataPitchBytes = (width * pixelBits) / 8;

		for (auto h=0; h < height; h++)
		{
			memcpy(data, baseAddr, MIN(dataPitchBytes, length));

			// Have we filled the data buffer?
			length -= dataPitchBytes;
			if (length <= 0)
				break;

			data += dataPitchBytes;
			baseAddr += texPitchBytes;
		}
	}
}

sce::Gnm::Texture* Texture::GetInternalData() const
{
	return _texture;
}

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD
#define STBI_NO_BMP
#define STBI_NO_TGA
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#include "stb_image.h"

bool Texture::Init2DFromStream(unsigned char* data, uint32_t length, CS_OUT int32_t *width, CS_OUT int32_t *height)
{
	assert(_texture == nullptr);

	int c, w, h;
	auto image = stbi_load_from_memory(data, length, &w, &h, &c, 4);
	if (image == nullptr)
	{
		*width = 0;
		*height = 0;
		return false;
	}

	// If the original image before conversion had alpha...
	if (c == 4)
	{
		// XNA blacks out any pixels with an alpha of zero.
		for (int i = 0; i < w * h; i += 4)
		{
			if (image[i + 3] == 0)
			{
				image[i + 0] = 0;
				image[i + 1] = 0;
				image[i + 2] = 0;
			}
		}
	}

	Init2D(TextureFormat::TextureFormat_Color, w, h, 1);
	SetData(0, image, 0, w * h * 4);
	STBI_FREE(image);

	*width = w;
	*height = h;

	return true;
}