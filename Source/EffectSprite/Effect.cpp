#include "Effect.h"

bool Effect::initGLProgramState(const std::string &fragmentFilename)
{
	FileUtils* fileUtiles = FileUtils::getInstance();
	std::string fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
	std::string fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
	GLProgram* glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());

	_glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
	_glprogramstate->retain();

	return _glprogramstate != nullptr;
}

Effect::Effect() : _glprogramstate(nullptr)
{
}

Effect::~Effect()
{
	CC_SAFE_RELEASE_NULL(_glprogramstate);
}

