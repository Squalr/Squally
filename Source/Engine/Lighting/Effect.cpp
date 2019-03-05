#include "Effect.h"

#include "cocos/platform/CCFileUtils.h"
#include "cocos/renderer/CCGLProgram.h"
#include "cocos/renderer/CCGLProgramState.h"
#include "cocos/renderer/ccShaders.h"

using namespace cocos2d;

bool Effect::initGLProgramState(const std::string &fragmentFilename)
{
    FileUtils* fileUtiles = FileUtils::getInstance();
    std::string fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
    std::string fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    GLProgram* glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    
    this->_glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    this->_glprogramstate->retain();
    
    return this->_glprogramstate != nullptr;
}

Effect::Effect()
{
	this->_glprogramstate = nullptr;
}

Effect::~Effect()
{
    CC_SAFE_RELEASE_NULL(this->_glprogramstate);
}
