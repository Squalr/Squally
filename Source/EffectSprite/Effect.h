#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Effect : public cocos2d::Ref
{
public:
	cocos2d::GLProgramState* getGLProgramState() const { return _glprogramstate; }

protected:
	Effect();
	virtual ~Effect();

	bool initGLProgramState(const std::string &fragmentFilename);
	cocos2d::GLProgramState* _glprogramstate;
};
