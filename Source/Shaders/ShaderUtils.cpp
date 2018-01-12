#include "ShaderUtils.h"

void ShaderUtils::applyDefaultFragShader(Node *node)
{
	node->setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	node->getGLProgram()->use();
}

void ShaderUtils::applyGrayscaleFragShader(Node *node)
{
	GLProgram *shader;
	const GLchar *fragmentShader;

	shader = GLProgram::createWithByteArrays(ccPositionTextureA8Color_vert, ccPositionTexture_GrayScale_frag);

	shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

	shader->link();
	CHECK_GL_ERROR_DEBUG();

	shader->updateUniforms();
	CHECK_GL_ERROR_DEBUG();

	node->setGLProgram(shader);
	node->getGLProgram()->use();
}
