#pragma once
#include <string>

#include "cocos/base/CCRef.h"

namespace cocos2d
{
	class GLProgramState;
}

class Effect : public cocos2d::Ref
{
public:
    cocos2d::GLProgramState* getGLProgramState() const { return _glprogramstate; }
    
protected:
    Effect();
    virtual ~Effect();

    bool initGLProgramState(const std::string& fragmentFilename);

    cocos2d::GLProgramState* _glprogramstate;
};
