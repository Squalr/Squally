#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class FloatingSprite : public Node
{
public:
	static FloatingSprite* create(std::string spriteResourcePath, Vec2 movement, Vec2 time);

	void setFlippedX(bool flipped);
	void setFlippedY(bool flipped);

protected:
	FloatingSprite(std::string spriteResourcePath, Vec2 movement, Vec2 time);
	~FloatingSprite();

	Sprite* sprite;
};