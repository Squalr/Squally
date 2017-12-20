#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class FloatingSprite : public Sprite
{
public:
	static FloatingSprite* create(std::string spriteResourcePath);

protected:
	FloatingSprite(std::string spriteResourcePath);
	~FloatingSprite();

	void update(float dt) override;

	Sprite* nodeA;
};