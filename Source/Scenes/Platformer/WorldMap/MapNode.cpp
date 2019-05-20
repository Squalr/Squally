#include "MapNode.h"

#include "Resources/UIResources.h"

#include "Engine/Input/ClickableNode.h"

using namespace cocos2d;

MapNode* MapNode::create(std::string mapFile)
{
	MapNode* instance = new MapNode(mapFile);

	instance->autorelease();

	return instance;
}

MapNode::MapNode(std::string mapFile)
{
	this->nodeMapFile = mapFile;
	this->mapSprite = ClickableNode::create(UIResources::Menus_WorldMap_MarkerCurrent, UIResources::Menus_WorldMap_MarkerCurrentSelected);

	this->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->addChild(this->mapSprite);
}

MapNode::~MapNode()
{
}

void MapNode::setLocked(bool newLocked)
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

bool MapNode::isLocked()
{
	return this->locked;
}

void MapNode::initializePositions()
{
	super::initializePositions();

	this->setContentSize(this->mapSprite->getContentSize());
}

void MapNode::initializeListeners()
{
	super::initializeListeners();

	this->mapSprite->setMouseClickCallback(CC_CALLBACK_0(MapNode::onNodeClick, this));
}

void MapNode::onNodeClick()
{
	NavigationEvents::navigatePlatformerMap(NavigationEvents::NavigateMapArgs(this->nodeMapFile, ""));
}
