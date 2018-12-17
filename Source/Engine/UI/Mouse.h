#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventCustom;
	class Sprite;
	class Vec2;
}

class Mouse : public SmartNode
{
public:
	static Mouse * create();

	const cocos2d::Vec2& getPosition() const override;

protected:
	Mouse();
	virtual ~Mouse();

private:
	void onEnter() override;
	void initializeListeners() override;
	void pause() override;
	void resume() override;
	void onMouseStateUpdateEvent(cocos2d::EventCustom* eventCustom);
	void setActiveMouseSprite(cocos2d::Sprite* mouseSprite);
	void setSpriteToCursorPosition();

	cocos2d::Vec2 readMousePosition;
	cocos2d::Sprite* activeMouseSprite;
	cocos2d::Sprite* mouseSpriteIdle;
	cocos2d::Sprite* mouseSpritePoint;
	cocos2d::Sprite* mouseSpritePointPressed;
	cocos2d::Sprite* mouseSpriteDrag;
};

