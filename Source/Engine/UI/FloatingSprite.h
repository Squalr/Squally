#pragma once
#include <string>

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

private:
	typedef SmartNode super;

	cocos2d::Sprite* sprite = nullptr;
	cocos2d::Vec2 movement = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 time = cocos2d::Vec2::ZERO;
};