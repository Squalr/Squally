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

	struct CursorSet
	{
		std::string mouseSpriteIdleResource;
		std::string mouseSpritePointResource;
		std::string mouseSpritePointPressedResource;
		std::string mouseSpriteDragResource;

		CursorSet() { }
		CursorSet(std::string mouseSpriteIdleResource, std::string mouseSpritePointResource, std::string mouseSpritePointPressedResource, std::string mouseSpriteDragResource) :
			mouseSpriteIdleResource(mouseSpriteIdleResource), mouseSpritePointResource(mouseSpritePointResource), mouseSpritePointPressedResource(mouseSpritePointPressedResource), mouseSpriteDragResource(mouseSpriteDragResource) { }
	};

	void registerCursorSet(int setId, CursorSet cursorSet);
	void setActiveCursorSet(int setId);
	int getActiveCursorSet();

	static const int SET_ID_DEFAULT = 0;
	static const int SET_ID_TRANSLATION_CURSOR = 1;

protected:
	Mouse();
	virtual ~Mouse();

private:
	typedef GlobalNode super;
	void onEnter() override;
	void initializeListeners() override;
	void onEventMouseStateUpdate(cocos2d::EventCustom* eventCustom);
	void setActiveMouseSprite(cocos2d::Node* mouseSprite);
	void setSpriteToCursorPosition();

	Hud* mouseHud;

	cocos2d::Vec2 readMousePosition;
	cocos2d::Node* activeMouseSprite;
	cocos2d::Node* mouseSpriteIdle;
	cocos2d::Node* mouseSpritePoint;
	cocos2d::Node* mouseSpritePointPressed;
	cocos2d::Node* mouseSpriteDrag;
	int activeCursorSet;
	std::map<int, CursorSet> cursorSets;

	static Mouse* instance;
};
