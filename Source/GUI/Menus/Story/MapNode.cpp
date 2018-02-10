#include "MapNode.h"

MapNode* MapNode::create(std::string resource, std::string resourceSelected, std::string resourceLocked, std::string mapName, std::string mapFile)
{
	MapNode* mapNode = new MapNode(resource, resourceSelected, resourceLocked, mapName, mapFile);

	mapNode->autorelease();

	return mapNode;
}

MapNode::MapNode(std::string resource, std::string resourceSelected, std::string resourceLocked, std::string mapName, std::string mapFile)
{
	this->nodeMapName = mapName;
	this->nodeMapFile = mapFile;
	this->onMouseOverEvent = nullptr;

	this->mapSprite = MenuSprite::create(resource, resourceSelected, resourceSelected);
	this->mapSpriteLocked = Sprite::create(resourceLocked);

	this->mapSpriteLocked->setVisible(false);

	this->addChild(this->mapSprite);
	this->addChild(this->mapSpriteLocked);

	this->initializePositions();
	this->initializeListeners();
}

MapNode::~MapNode()
{
}

void MapNode::setLocked(bool isLocked)
{
	if (isLocked)
	{
		this->mapSprite->setVisible(false);
		this->mapSpriteLocked->setVisible(true);
	}
	else
	{
		this->mapSprite->setVisible(true);
		this->mapSpriteLocked->setVisible(false);
	}
}

void MapNode::setCallBack(std::function<void(MapNode*)> onMouseOver)
{
	this->onMouseOverEvent = onMouseOver;
}

void MapNode::initializePositions()
{
	this->setContentSize(this->mapSpriteLocked->getContentSize());
}

void MapNode::initializeListeners()
{
	this->mapSprite->setClickCallback(CC_CALLBACK_2(MapNode::onNodeClick, this));
}

void MapNode::onNodeClick(MenuSprite* menuSprite, EventMouse* args)
{
	Director::getInstance()->replaceScene(Level::create(this->nodeMapFile));
}
