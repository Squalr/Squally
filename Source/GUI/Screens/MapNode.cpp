#include "MapNode.h"

MapNode::MapNode(Vec2 position, bool tutorialNode)
{
	if (tutorialNode)
	{
		this->sprite = Sprite::create(Resources::GUI_WorldMaps_TutorialNodeUnlocked);
	}
	else
	{
		this->sprite = Sprite::create(Resources::GUI_WorldMaps_LevelNodeUnlocked);
	}

	this->sprite->setPosition(position);

	this->addChild(this->sprite);
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

	mouseListener->onMouseDown = CC_CALLBACK_1(MapNode::OnMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MapNode::OnMouseDown(EventMouse* event)
{
	Director::getInstance()->replaceScene(new Level());
}

