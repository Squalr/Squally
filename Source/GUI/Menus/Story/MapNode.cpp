#include "MapNode.h"

MapNode* MapNode::create(std::string mapName, std::string mapFile, Vec2 position)
{
	MapNode* mapNode = new MapNode(mapName, mapFile, position);

	mapNode->autorelease();

	return mapNode;
}

MapNode::MapNode(std::string mapName, std::string mapFile, Vec2 position)
{
	this->nodeMapName = mapName;
	this->nodeMapFile = mapFile;
	this->setPosition(position);
	this->onMouseOverEvent = nullptr;

	this->sprite = Sprite::create(Resources::Menus_WorldMaps_LevelNodeUnlocked);
	this->spriteSelected = Sprite::create(Resources::Menus_WorldMaps_TutorialNodeSelected);

	this->setContentSize(this->sprite->getContentSize());

	this->spriteSelected->setVisible(false);

	this->addChild(this->sprite);
	this->addChild(this->spriteSelected);

	this->initializeListeners();
}

MapNode::~MapNode()
{
}

void MapNode::setCallBack(std::function<void(MapNode*)> onMouseOver)
{
	this->onMouseOverEvent = onMouseOver;
}

void MapNode::initializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(MapNode::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MapNode::onMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MapNode::onMouseMove(EventMouse* event)
{
	if (Utils::intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
	{
		this->sprite->setVisible(false);
		this->spriteSelected->setVisible(true);
		this->onMouseOverEvent(this);
	}
	else
	{
		this->sprite->setVisible(true);
		this->spriteSelected->setVisible(false);
	}
}

void MapNode::onMouseDown(EventMouse* event)
{
	if (Utils::intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
	{
		Director::getInstance()->replaceScene(Level::create(this->nodeMapFile));
	}
}

