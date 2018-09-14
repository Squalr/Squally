#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class ShaderUtils
{
public:
	static void applyDefaultFragShader(Node *node);
	static void applyGrayscaleFragShader(Node *node);
};
