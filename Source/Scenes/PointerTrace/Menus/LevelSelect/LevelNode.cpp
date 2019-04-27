#include "LevelNode.h"

#include "Resources/UIResources.h"

#include "Engine/Input/ClickableNode.h"

using namespace cocos2d;

LevelNode* LevelNode::create(std::string mapFile)
{
	LevelNode* instance = new LevelNode(mapFile);

	instance->autorelease();

	return instance;
}

LevelNode::LevelNode(std::string mapFile)
{
	this->nodeMapFile = mapFile;
	this->mapSprite = ClickableNode::create(UIResources::Menus_WorldMap_MarkerCurrent, UIResources::Menus_WorldMap_MarkerCurrentSelected);

	this->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->addChild(this->mapSprite);
}

LevelNode::~LevelNode()
{
}

void LevelNode::setLocked(bool newLocked)
{
	if (newLocked)
	{
		this->mapSprite->setVisible(false);
	}
	else
	{
		this->mapSprite->setVisible(true);
	}

	this->locked = newLocked;
}

bool LevelNode::isLocked()
{
	return this->locked;
}

void LevelNode::initializePositions()
{
	super::initializePositions();

	this->setContentSize(this->mapSprite->getContentSize());
}

void LevelNode::initializeListeners()
{
	super::initializeListeners();

	this->mapSprite->setMouseClickCallback(CC_CALLBACK_0(LevelNode::onNodeClick, this));
}

void LevelNode::onNodeClick()
{
	NavigationEvents::navigateLoadingScreen(NavigationEvents::NavigateLoadingScreenArgs(this->nodeMapFile, [](SerializableMap* map)
	{
		NavigationEvents::navigateMap(NavigationEvents::NavigateMapArgs(map));
	}));
}
