#pragma once

#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Sprite;
	class Vec2;
}

class Hud;

class Mouse : public GlobalNode
{
public:
	static void RegisterGlobalNode();
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

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef GlobalNode super;
	
	void setActiveMouseSprite(cocos2d::Node* mouseSprite);
	void setSpriteToCursorPosition();

	Hud* mouseHud = nullptr;

	cocos2d::Vec2 readMousePosition;
	cocos2d::Node* activeMouseSprite = nullptr;
	cocos2d::Node* mouseSpriteIdle = nullptr;
	cocos2d::Node* mouseSpritePoint = nullptr;
	cocos2d::Node* mouseSpritePointPressed = nullptr;
	cocos2d::Node* mouseSpriteDrag = nullptr;
	int activeCursorSet = -1;
	std::map<int, CursorSet> cursorSets;

	static Mouse* Instance;
};
