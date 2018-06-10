#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class FloatingSprite : public Sprite
{
public:
	static FloatingSprite* create(std::string spriteResourcePath, Vec2 movement, Vec2 time);

protected:
	FloatingSprite(std::string spriteResourcePath, Vec2 movement, Vec2 time);
	~FloatingSprite();
};