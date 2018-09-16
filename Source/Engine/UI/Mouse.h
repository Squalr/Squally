#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/MouseState.h"
#include "Resources.h"

using namespace cocos2d;

class Mouse : public SmartNode
{
public:
	static Mouse * create();

protected:
	Mouse();
	~Mouse();

private:
	void initializeListeners() override;
	void onEnter() override;
	void pause() override;
	void resume() override;
	void onMouseStateUpdateEvent(EventCustom* eventCustom);
	void setActiveMouseSprite(Sprite* mouseSprite);
	void setSpriteToCursorPosition();

	Sprite* activeMouseSprite;
	Sprite* mouseSpriteIdle;
	Sprite* mouseSpritePoint;
	Sprite* mouseSpritePointPressed;
	Sprite* mouseSpriteDrag;
};

