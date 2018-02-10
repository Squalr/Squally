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
	this->titleLabel = OutlineLabel::create("Level Select", Resources::Fonts_Montserrat_Medium, this->titleFontSize);
	this->infoLabel = OutlineLabel::create("Level 1", Resources::Fonts_Montserrat_Medium, this->infoFontSize);
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
		Director::getInstance()->popScene();
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

		if (Utils::intersects(node, mouseCoords))
		{
			this->infoLabel->setText(node->nodeMapName);
			return;
		}
	}

	this->infoLabel->setText("");
}
