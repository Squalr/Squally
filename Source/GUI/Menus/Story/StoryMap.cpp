#include "StoryMap.h"

StoryMap * StoryMap::create()
{
	StoryMap* storyMap = new StoryMap();

	storyMap->autorelease();

	return storyMap;
}

StoryMap::StoryMap()
{
	this->mapNodes = new std::vector<MapNode*>();
	this->background = Sprite::create(Resources::Menus_WorldMaps_StoryMap);
	this->foreground = Sprite::create(Resources::Menus_WorldMaps_StoryMapFront);
	this->infoPanel = Sprite::create(Resources::Menus_WorldMaps_MapPanel);
	this->titleLabel = Label::create("Level Select", Resources::Fonts_Montserrat_Medium, this->titleFontSize);
	this->infoLabel = Label::create("", Resources::Fonts_Montserrat_Medium, this->infoFontSize);

	this->titleLabel->enableOutline(Color4B::BLACK, 2.0f);
	this->infoLabel->enableOutline(Color4B::BLACK, 2.0f);

	this->jungle = MapNode::create(
		Resources::Menus_WorldMaps_Jungle,
		Resources::Menus_WorldMaps_JungleSelected,
		Resources::Menus_WorldMaps_JungleLocked,
		"Jungle",
		Resources::Levels_Jungle
	);

	this->waterRuins = MapNode::create(
		Resources::Menus_WorldMaps_WaterRuins,
		Resources::Menus_WorldMaps_WaterRuinsSelected,
		Resources::Menus_WorldMaps_WaterRuinsLocked,
		"Aquatic Ruins",
		Resources::Levels_AquaticRuins
	);

	this->forest = MapNode::create(
		Resources::Menus_WorldMaps_Forest,
		Resources::Menus_WorldMaps_ForestSelected,
		Resources::Menus_WorldMaps_ForestLocked,
		"Forest",
		Resources::Levels_Forest
	);

	this->caverns = MapNode::create(
		Resources::Menus_WorldMaps_Mountain,
		Resources::Menus_WorldMaps_MountainSelected,
		Resources::Menus_WorldMaps_MountainLocked,
		"Caverns",
		Resources::Levels_Caverns
	);

	this->iceCaps = MapNode::create(
		Resources::Menus_WorldMaps_IceMountain,
		Resources::Menus_WorldMaps_IceMountainSelected,
		Resources::Menus_WorldMaps_IceMountainLocked,
		"Ice Caps",
		Resources::Levels_IceCaps
	);

	this->obelisk = MapNode::create(
		Resources::Menus_WorldMaps_Monolith,
		Resources::Menus_WorldMaps_MonolithSelected,
		Resources::Menus_WorldMaps_MonolithLocked,
		"The Obelisk",
		Resources::Levels_Obelisk
	);

	this->volcano = MapNode::create(
		Resources::Menus_WorldMaps_Volcano,
		Resources::Menus_WorldMaps_VolcanoSelected,
		Resources::Menus_WorldMaps_VolcanoLocked,
		"Volcano",
		Resources::Levels_Volcano
	);

	this->mapNodes->push_back(this->jungle);
	this->mapNodes->push_back(this->waterRuins);
	this->mapNodes->push_back(this->forest);
	this->mapNodes->push_back(this->caverns);
	this->mapNodes->push_back(this->iceCaps);
	this->mapNodes->push_back(this->obelisk);
	this->mapNodes->push_back(this->volcano);

	this->addChild(this->background);
	this->addChild(this->jungle);
	this->addChild(this->waterRuins);
	this->addChild(this->forest);
	this->addChild(this->caverns);
	this->addChild(this->iceCaps);
	this->addChild(this->obelisk);
	this->addChild(this->volcano);
	this->addChild(this->foreground);
	this->addChild(this->infoPanel);
	this->addChild(this->titleLabel);
	this->addChild(this->infoLabel);

	this->initializeListeners();
}

StoryMap::~StoryMap()
{
	delete(this->mapNodes);
}

void StoryMap::onEnter()
{
	FadeScene::onEnter();

	this->initializePositions();

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->infoPanel, delay, duration);
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->infoLabel, delay, duration);

	this->addChild(Mouse::claimInstance());
}

void StoryMap::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->infoPanel->setPosition(Vec2(visibleSize.width / 2.0f - 616.0f, visibleSize.height - this->infoPanel->getContentSize().height / 2.0f - 24.0f));
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f - 616.0f, visibleSize.height - this->titleLabel->getContentSize().height / 2.0f - 64.0f));
	this->infoLabel->setPosition(Vec2(visibleSize.width / 2.0f - 616.0f, visibleSize.height - 48.0f - 64.0f - 48.0f));
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->jungle->setPosition(Vec2(visibleSize.width / 2.0f + 624.0f, visibleSize.height / 2.0f - 292.0f));
	this->waterRuins->setPosition(Vec2(visibleSize.width / 2.0f - 104.0f, visibleSize.height / 2.0f - 340.0f));
	this->forest->setPosition(Vec2(visibleSize.width / 2.0f - 688.0f, visibleSize.height / 2.0f - 340.0f));
	this->caverns->setPosition(Vec2(visibleSize.width / 2.0f - 564.0f, visibleSize.height / 2.0f + 180.0f));
	this->iceCaps->setPosition(Vec2(visibleSize.width / 2.0f + 112.0f, visibleSize.height / 2.0f + 496.0f));
	this->obelisk->setPosition(Vec2(visibleSize.width / 2.0f + 720.0f, visibleSize.height / 2.0f + 420.0f));
	this->volcano->setPosition(Vec2(visibleSize.width / 2.0f + 168.0f, visibleSize.height / 2.0f + 72.0f));
	this->foreground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void StoryMap::initializeListeners()
{
	EventListenerCustom* customListener = EventListenerCustom::create(Mouse::MouseMoveEvent, CC_CALLBACK_1(StoryMap::onMouseSpriteMove, this));
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(StoryMap::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void StoryMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		GameUtils::navigateBack();
		break;
	}
}

void StoryMap::onMouseSpriteMove(EventCustom* event)
{
	Mouse::MouseEventArgs* args = static_cast<Mouse::MouseEventArgs*>(event->getUserData());
	Vec2 mouseCoords = Vec2(args->mouseX, args->mouseY);

	for (auto it = this->mapNodes->begin(); it != this->mapNodes->end(); it++)
	{
		MapNode* node = *it;

		if (GameUtils::intersects(node, mouseCoords))
		{
			this->infoLabel->setString(node->nodeMapName);
			return;
		}
	}

	this->infoLabel->setString("");
}
