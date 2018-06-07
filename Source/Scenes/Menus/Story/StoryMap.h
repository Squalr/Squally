#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Events/MouseEvents.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "MapNode.h"

using namespace cocos2d;

class StoryMap : public FadeScene
{
public:
	static StoryMap * create();

protected:
	StoryMap();
	~StoryMap();

private:
	void onEnter() override;
	void initializedLocked();
	void initializePositions();
	void initializeListeners();
	void onMouseSpriteMove(EventCustom* args);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	std::vector<MapNode*>* mapNodes;
	MapNode* jungle;
	MapNode* waterRuins;
	MapNode* forest;
	MapNode* caverns;
	MapNode* castle;
	MapNode* iceCaps;
	MapNode* obelisk;
	MapNode* volcano;
	MapNode* mecha;

	Sprite* background;
	Sprite* foreground;
	InfiniteParallaxNode* fogA;
	InfiniteParallaxNode* fogB;
	InfiniteParallaxNode* fogC;
	Label* titleLabel;
	Label* infoLabel;

	const float titleFontSize = 48.0f;
	const float infoFontSize = 32.0f;
};

