#pragma once
#include "cocos/math/CCGeometry.h"

namespace cocos2d
{
	class DrawNode;
	class GLProgram;
	class GLProgramState;
	class Sprite;
}

class RenderUtils
{
public:
	static cocos2d::Sprite* renderDrawNode(cocos2d::DrawNode* drawNode, cocos2d::Vec2 offset, cocos2d::Size renderSize);
	static cocos2d::Sprite* applyShaderOnce(cocos2d::Sprite* sprite, cocos2d::GLProgram* program,
			cocos2d::GLProgramState* state);
};
