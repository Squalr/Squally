#pragma once
#include <string>

#include "cocos/2d/CCSprite.h"
#include "cocos/math/Vec2.h"

class FloatingSprite : public cocos2d::Sprite
{
public:
	static FloatingSprite* create(std::string spriteResourcePath, cocos2d::Vec2 movement, cocos2d::Vec2 time);

protected:
	FloatingSprite(std::string spriteResourcePath, cocos2d::Vec2 movement, cocos2d::Vec2 time);
	virtual ~FloatingSprite();
};