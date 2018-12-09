#pragma once
#include "cocos2d.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/GlobalScene.h"
#include "Engine/Localization/Localization.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"

#include "MapNode.h"

using namespace cocos2d;

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
	void onMouseMove(EventCustom* args);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	std::vector<MapNode*> mapNodes;
	MapNode* jungle;
	MapNode* waterRuins;
	MapNode* forest;
	MapNode* caverns;
	MapNode* castle;
	MapNode* iceCaps;
	MapNode* obelisk;
	MapNode* volcano;
	MapNode* mech;

	Sprite* background;
	Sprite* foreground;
	InfiniteParallaxNode* fogA;
	InfiniteParallaxNode* fogB;
	InfiniteParallaxNode* fogC;
	Label* titleLabel;
	Label* infoLabel;

	static WorldMap* instance;

	const float titleFontSize = 48.0f;
	const float infoFontSize = 32.0f;

	static const std::string StringKeySelectLevel;
	static const std::string StringKeyLevelNameJungle;
	static const std::string StringKeyLevelNameAquaticRuins;
	static const std::string StringKeyLevelNameForest;
	static const std::string StringKeyLevelNameCaverns;
	static const std::string StringKeyLevelNameCastle;
	static const std::string StringKeyLevelNameIceCaps;
	static const std::string StringKeyLevelNameObelisk;
	static const std::string StringKeyLevelNameVolcano;
	static const std::string StringKeyLevelNameMech;
};

