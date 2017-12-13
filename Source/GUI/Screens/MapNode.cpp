#include "MapNode.h"

MapNode::MapNode(Vec2 position, bool tutorialNode)
{
	this->setPosition(position);

	if (tutorialNode)
	{
		this->sprite = Sprite::create(Resources::GUI_WorldMaps_TutorialNodeUnlocked);
		this->spriteSelected = Sprite::create(Resources::GUI_WorldMaps_TutorialNodeSelected);
	}
	else
	{
		this->sprite = Sprite::create(Resources::GUI_WorldMaps_LevelNodeUnlocked);
		this->spriteSelected = Sprite::create(Resources::GUI_WorldMaps_TutorialNodeSelected);
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
		Director::getInstance()->replaceScene(new Level());
	}
}

