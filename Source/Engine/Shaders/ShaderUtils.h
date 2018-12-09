#pragma once

namespace cocos2d
{
	class Node;
}

class ShaderUtils
{
public:
	static void applyDefaultFragShader(cocos2d::Node *node);
	static void applyGrayscaleFragShader(cocos2d::Node *node);
};
