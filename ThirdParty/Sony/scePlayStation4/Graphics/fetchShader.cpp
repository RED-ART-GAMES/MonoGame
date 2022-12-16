#include "fetchShader.h"

#include "vertexShader.h"
#include "..\allocator.h"

#include <sdk_version.h>
#include <gnm.h>
#include <gnmx.h>
#include <gnmx/shader_parser.h>
#include <assert.h>

using namespace sce;
using namespace sce::Gnmx;
using namespace Graphics;


FetchShader::FetchShader(VertexShader *shader, const uint32_t* remap, int32_t count)
{
	auto fetchSize = Gnmx::computeVsFetchShaderSize(shader->_shader);

	_fsMem = mem::allocShared(fetchSize, Gnm::kAlignmentOfFetchShaderInBytes);

#if SCE_ORBIS_SDK_VERSION >= 0x05008041u // SDK Version 5.0
	Gnmx::generateVsFetchShader(_fsMem, &_shaderModifier, shader->_shader, NULL, 0, remap, count);
#else
	Gnmx::generateVsFetchShader(_fsMem, &_shaderModifier, shader->_shader, NULL, remap, count);
#endif

}

FetchShader::~FetchShader()
{
	mem::freeShared(_fsMem);
}
