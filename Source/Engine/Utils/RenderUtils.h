#pragma once
#include <functional>

#include "cocos/math/CCGeometry.h"

namespace cocos2d
{
	class GLProgram;
	class GLProgramState;
	class Node;
	class RenderTexture;
	class Sprite;
}

class RenderUtils
{
public:
	static cocos2d::Sprite* renderNodeToSprite(cocos2d::Node* target, cocos2d::Vec2 offset, cocos2d::Size renderSize, cocos2d::Size padding = cocos2d::Size::ZERO);
	static cocos2d::Sprite* applyShaderOnce(cocos2d::Sprite* target, std::string vertexShader, std::string fragmentShader, std::function<void(cocos2d::GLProgramState*)> bindStateVariablesCallback = nullptr);
	static void applyShader(cocos2d::Node* target, std::string vertexShader, std::string fragmentShader, std::function<void(cocos2d::GLProgramState*)> bindStateVariablesCallback = nullptr);
};
