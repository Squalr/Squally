#pragma once
#include <functional>

#include "cocos/math/CCGeometry.h"
#include "cocos/math/Vec2.h"

namespace cocos2d
{
	class GLProgramState;
	class Node;
	class Sprite;
}

class RenderUtils
{
public:
	static cocos2d::Sprite* renderNodeToSprite(cocos2d::Node* target, cocos2d::Vec2 offset, cocos2d::CSize renderSize, cocos2d::CSize padding = cocos2d::CSize::ZERO);
	static cocos2d::Sprite* applyShaderOnce(cocos2d::Sprite* target, std::string vertexShader, std::string fragmentShader, std::function<void(cocos2d::GLProgramState*)> bindStateVariablesCallback = nullptr);
	static void applyShader(cocos2d::Node* target, std::string vertexShader, std::string fragmentShader, std::function<void(cocos2d::GLProgramState*)> bindStateVariablesCallback = nullptr);
};
