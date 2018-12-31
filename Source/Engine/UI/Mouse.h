#pragma once

#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class EventCustom;
	class Sprite;
	class Vec2;
}

class Hud;

class Mouse : public GlobalNode
{
public:
	static void registerGlobalNode();
	static Mouse* getInstance();

	const cocos2d::Vec2& getPosition() const override;

protected:
	Mouse();
	virtual ~Mouse();

private:
	typedef GlobalNode super;
	void onEnter() override;
	void initializeListeners() override;
	void onMouseStateUpdateEvent(cocos2d::EventCustom* eventCustom);
	void setActiveMouseSprite(cocos2d::Sprite* mouseSprite);
	void setSpriteToCursorPosition();

	Hud* mouseHud;

	cocos2d::Vec2 readMousePosition;
	cocos2d::Sprite* activeMouseSprite;
	cocos2d::Sprite* mouseSpriteIdle;
	cocos2d::Sprite* mouseSpritePoint;
	cocos2d::Sprite* mouseSpritePointPressed;
	cocos2d::Sprite* mouseSpriteDrag;

	static Mouse* instance;
};

