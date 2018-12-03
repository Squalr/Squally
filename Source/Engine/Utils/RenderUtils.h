#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class RenderUtils
{
public:
	static Sprite* renderDrawNode(DrawNode* drawNode, Vec2 offset, Size renderSize);
	static Sprite* applyShaderOnce(Sprite* sprite, GLProgram* program, GLProgramState* state);
};
