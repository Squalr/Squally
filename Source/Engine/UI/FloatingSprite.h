#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class FloatingSprite : public SmartNode
{
public:
	static FloatingSprite* create(std::string spriteResourcePath, cocos2d::Vec2 movement, cocos2d::Vec2 time);

	void setFlippedX(bool isFlipped);
	void setFlippedY(bool isFlipped);

protected:
	FloatingSprite(std::string spriteResourcePath, cocos2d::Vec2 movement, cocos2d::Vec2 time);
	virtual ~FloatingSprite();

	void onEnter() override;

	cocos2d::Sprite* sprite;
	cocos2d::Vec2 movement;
	cocos2d::Vec2 time;
};