#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Event;
	class Sprite;
}

class Hud;
class Lightning;
class LightningSphere;
class MapNode;
class Mouse;

class WorldMap : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	WorldMap();
	~WorldMap();

private:
	void onEnter() override;
	void initializedLocked();
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	std::vector<MapNode*> mapNodes;
	MapNode* forest;
	MapNode* waterRuins;
	MapNode* caverns;
	MapNode* castle;
	MapNode* iceCaps;
	MapNode* volcano;
	MapNode* crypts;
	MapNode* voidStar;

	cocos2d::Sprite* background;
	cocos2d::Node* voidCrystalNode;
	cocos2d::Sprite* voidCrystal;
	LightningSphere* lightningSphere;
	Lightning* lightning1;
	Lightning* lightning2;
	Lightning* lightning3;
	Lightning* lightning4;
	Lightning* lightning5;
	Lightning* lightning6;
	Lightning* lightning7;
	Lightning* lightning8;
	Lightning* lightning9;
	Lightning* lightning10;

	Hud* hud;

	static WorldMap* instance;
};

