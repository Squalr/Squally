#include "TutorialItem.h"

TutorialItem::TutorialItem(std::string mapName, std::string mapFile, Vec2 position, bool tutorialNode, std::function<void(TutorialItem*)> onMouseOver)
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

TutorialItem::~TutorialItem()
{
}

void TutorialItem::onEnter()
{
	Node::onEnter();

	this->InitializeListeners();
}

void TutorialItem::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(TutorialItem::OnMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(TutorialItem::OnMouseDown, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void TutorialItem::OnMouseMove(EventMouse* event)
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

void TutorialItem::OnMouseDown(EventMouse* event)
{
	if (Utils::Intersects(this, Vec2(event->getCursorX(), event->getCursorY())))
	{
		Director::getInstance()->replaceScene(new Level(this->nodeMapFile));
	}
}

