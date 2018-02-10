#include "StoryMap.h"

StoryMap * StoryMap::create()
{
	StoryMap* storyMap = new StoryMap();

	storyMap->autorelease();

	return storyMap;
}

StoryMap::StoryMap()
{
	this->titleLabel = OutlineLabel::create("Level Select", Resources::Fonts_Marker_Felt, this->titleFontSize);
	this->infoLabel = OutlineLabel::create("Level 1", Resources::Fonts_Marker_Felt, this->infoFontSize);
	this->background = Sprite::create(Resources::Menus_WorldMaps_StoryMap);
	this->foreground = Sprite::create(Resources::Menus_WorldMaps_StoryMapFront);

	this->jungle = MapNode::create(
		Resources::Menus_WorldMaps_Jungle,
		Resources::Menus_WorldMaps_JungleSelected,
		Resources::Menus_WorldMaps_JungleLocked,
		"Jungle",
		Resources::Levels_TutorialExactScan1
	);

	this->waterRuins = MapNode::create(
		Resources::Menus_WorldMaps_WaterRuins,
		Resources::Menus_WorldMaps_WaterRuinsSelected,
		Resources::Menus_WorldMaps_WaterRuinsLocked,
		"Aquatic Ruins",
		Resources::Levels_TutorialExactScan1
	);

	this->forest = MapNode::create(
		Resources::Menus_WorldMaps_Forest,
		Resources::Menus_WorldMaps_ForestSelected,
		Resources::Menus_WorldMaps_ForestLocked,
		"Forest",
		Resources::Levels_TutorialExactScan1
	);

	this->caverns = MapNode::create(
		Resources::Menus_WorldMaps_Mountain,
		Resources::Menus_WorldMaps_MountainSelected,
		Resources::Menus_WorldMaps_MountainLocked,
		"Caverns",
		Resources::Levels_TutorialExactScan1
	);

	this->iceCaps = MapNode::create(
		Resources::Menus_WorldMaps_IceMountain,
		Resources::Menus_WorldMaps_IceMountainSelected,
		Resources::Menus_WorldMaps_IceMountainLocked,
		"Ice Caps",
		Resources::Levels_TutorialExactScan1
	);

	this->obelisk = MapNode::create(
		Resources::Menus_WorldMaps_Monolith,
		Resources::Menus_WorldMaps_MonolithSelected,
		Resources::Menus_WorldMaps_MonolithLocked,
		"The Obelisk",
		Resources::Levels_TutorialExactScan1
	);

	this->volcano = MapNode::create(
		Resources::Menus_WorldMaps_Volcano,
		Resources::Menus_WorldMaps_VolcanoSelected,
		Resources::Menus_WorldMaps_VolcanoLocked,
		"Volcano",
		Resources::Levels_TutorialExactScan1
	);


	this->addChild(this->background);
	this->addChild(this->jungle);
	this->addChild(this->waterRuins);
	this->addChild(this->forest);
	this->addChild(this->caverns);
	this->addChild(this->iceCaps);
	this->addChild(this->obelisk);
	this->addChild(this->volcano);
	this->addChild(this->foreground);
	this->addChild(this->titleLabel);
	this->addChild(this->infoLabel);

	this->initializeListeners();
}

StoryMap::~StoryMap()
{
}

void StoryMap::onEnter()
{
	FadeScene::onEnter();

	this->initializePositions();

	this->addChild(Mouse::claimInstance());
}

void StoryMap::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->titleLabel->getContentSize().height / 2));
	this->infoLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->infoLabel->getContentSize().height / 2 - 48));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->jungle->setPosition(Vec2(origin.x + visibleSize.width / 2 + 624.0f, origin.y + visibleSize.height / 2 - 292.0f));
	this->waterRuins->setPosition(Vec2(origin.x + visibleSize.width / 2 - 104.0f, origin.y + visibleSize.height / 2 - 340.0f));
	this->forest->setPosition(Vec2(origin.x + visibleSize.width / 2 - 688.0f, origin.y + visibleSize.height / 2 - 340.0f));
	this->caverns->setPosition(Vec2(origin.x + visibleSize.width / 2 - 564.0f, origin.y + visibleSize.height / 2 + 180.0f));
	this->iceCaps->setPosition(Vec2(origin.x + visibleSize.width / 2 + 112.0f, origin.y + visibleSize.height / 2 + 496.0f));
	this->obelisk->setPosition(Vec2(origin.x + visibleSize.width / 2 + 720.0f, origin.y + visibleSize.height / 2 + 420.0f));
	this->volcano->setPosition(Vec2(origin.x + visibleSize.width / 2 + 168.0f, origin.y + visibleSize.height / 2 + 72.0f));
	this->foreground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
}

void StoryMap::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(StoryMap::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void StoryMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->popScene();
		break;
	}
}
