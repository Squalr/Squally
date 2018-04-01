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

	this->castle = MapNode::create(
		Resources::Menus_WorldMaps_Castle,
		Resources::Menus_WorldMaps_CastleSelected,
		Resources::Menus_WorldMaps_CastleLocked,
		"Castle",
		Resources::Levels_Castle
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

	this->mecha = MapNode::create(
		Resources::Menus_WorldMaps_Mecha,
		Resources::Menus_WorldMaps_MechaSelected,
		Resources::Menus_WorldMaps_MechaLocked,
		"Mecha",
		Resources::Levels_Mecha
	);

	this->mapNodes->push_back(this->jungle);
	this->mapNodes->push_back(this->waterRuins);
	this->mapNodes->push_back(this->forest);
	this->mapNodes->push_back(this->caverns);
	this->mapNodes->push_back(this->castle);
	this->mapNodes->push_back(this->iceCaps);
	this->mapNodes->push_back(this->obelisk);
	this->mapNodes->push_back(this->volcano);
	this->mapNodes->push_back(this->mecha);

	this->addChild(this->background);
	this->addChild(this->jungle);
	this->addChild(this->waterRuins);
	this->addChild(this->forest);
	this->addChild(this->caverns);
	this->addChild(this->castle);
	this->addChild(this->iceCaps);
	this->addChild(this->obelisk);
	this->addChild(this->volcano);
	this->addChild(this->mecha);
	this->addChild(this->foreground);
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

	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->infoLabel, delay, duration);

	this->addChild(Mouse::claimInstance());
}

void StoryMap::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f - 616.0f, visibleSize.height - this->titleLabel->getContentSize().height / 2.0f - 64.0f));
	this->infoLabel->setPosition(Vec2(visibleSize.width / 2.0f - 616.0f, visibleSize.height - 48.0f - 64.0f - 48.0f));
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->jungle->setPosition(Vec2(visibleSize.width / 2.0f + 624.0f, visibleSize.height / 2.0f - 292.0f));
	this->waterRuins->setPosition(Vec2(visibleSize.width / 2.0f - 104.0f, visibleSize.height / 2.0f - 340.0f));
	this->forest->setPosition(Vec2(visibleSize.width / 2.0f - 704.0f, visibleSize.height / 2.0f - 308.0f));
	this->caverns->setPosition(Vec2(visibleSize.width / 2.0f - 668.0f, visibleSize.height / 2.0f + 32.0f));
	this->castle->setPosition(Vec2(visibleSize.width / 2.0f - 388.0f, visibleSize.height / 2.0f + 344.0f));
	this->iceCaps->setPosition(Vec2(visibleSize.width / 2.0f + 112.0f, visibleSize.height / 2.0f + 496.0f));
	this->obelisk->setPosition(Vec2(visibleSize.width / 2.0f + 720.0f, visibleSize.height / 2.0f + 420.0f));
	this->volcano->setPosition(Vec2(visibleSize.width / 2.0f + 196.0f, visibleSize.height / 2.0f + 64.0f));
	this->mecha->setPosition(Vec2(visibleSize.width / 2.0f + 696.0f, visibleSize.height / 2.0f - 38.0f));
	this->foreground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	this->initializedLocked();
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

void StoryMap::initializedLocked()
{
	MapNode* jungle;
	MapNode* waterRuins;
	MapNode* forest;
	MapNode* caverns;
	MapNode* iceCaps;
	MapNode* obelisk;
	MapNode* volcano;

	this->jungle->setLocked(false);
	this->waterRuins->setLocked(false);
	this->forest->setLocked(false);
	this->caverns->setLocked(false);
	this->castle->setLocked(false);
	this->iceCaps->setLocked(false);
	this->obelisk->setLocked(false);
	this->volcano->setLocked(false);
	this->mecha->setLocked(false);
}

void StoryMap::onMouseSpriteMove(EventCustom* event)
{
	Mouse::MouseEventArgs* args = static_cast<Mouse::MouseEventArgs*>(event->getUserData());
	Vec2 mouseCoords = Vec2(args->mouseX, args->mouseY);

	for (auto it = this->mapNodes->begin(); it != this->mapNodes->end(); it++)
	{
		MapNode* node = *it;

		if (GameUtils::intersects(node, mouseCoords) && !node->isLocked())
		{
			this->infoLabel->setString(node->nodeMapName);
			return;
		}
	}

	this->infoLabel->setString("");
}
