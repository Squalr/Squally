#include "MapNode.h"

MapNode::MapNode(std::string mapName, std::string mapFile, Vec2 position, bool tutorialNode, std::function<void(MapNode*)> onMouseOver)
{
	this->nodeMapName = mapName;
	this->nodeMapFile = mapFile;
	this->setPosition(position);
	this->onMouseOverEvent = onMouseOver;

	if (tutorialNode)
	{
		this->sprite = Sprite::create(Resources::Menus_WorldMaps_TutorialNodeUnlocked);
		this->spriteSelected = Sprite::create(Resources::Menus_WorldMaps_TutorialNodeSelected);
	}
	else
	{
		this->sprite = Sprite::create(Resources::Menus_WorldMaps_LevelNodeUnlocked);
		this->spriteSelected = Sprite::create(Resources::Menus_WorldMaps_TutorialNodeSelected);
	}

	this->setContentSize(this->sprite->getContentSize());

	this->spriteSelected->setVisible(false);

	this->addChild(this->sprite);
	this->addChild(this->spriteSelected);
}

MapNode::~MapNode()
{
}

void MapNode::onEnter()
{
	Node::onEnter();

	this->InitializeListeners();
}

void MapNode::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(MapNode::OnMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MapNode::OnMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MapNode::OnMouseMove(EventMouse* event)
{
	if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
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

void MapNode::OnMouseDown(EventMouse* event)
{
	if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
	{
		Director::getInstance()->replaceScene(new Level(this->nodeMapFile));
	}
}

