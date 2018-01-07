#include "HUD.h"

HUD* HUD::create()
{
	HUD* hud = new HUD();

	hud->autorelease();

	return hud;
}

HUD::HUD()
{
	this->heart = Sprite::create(Resources::HUD_Heart);
	this->healthBarFrame = Sprite::create(Resources::HUD_HealthBarFrame);
	this->dialogNode = Node::create();

	this->addChild(this->healthBarFrame);
	this->addChild(this->heart);
	this->addChild(this->dialogNode);

	this->initializeListeners();
}

HUD::~HUD()
{
}

void HUD::onEnter()
{
	Node::onEnter();

	this->initializePositions();
}

void HUD::initializePositions()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->healthBarFrame->setPosition(Vec2(origin.x + this->heart->getContentSize().width + this->healthBarFrame->getContentSize().width / 2, origin.y + visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
	this->heart->setPosition(Vec2(origin.x + this->heart->getContentSize().width / 2 + 16.0f, origin.y + visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
}

void HUD::initializeListeners()
{
	EventListenerCustom* customListener = EventListenerCustom::create(DialogMenu::DialogOpenEvent, CC_CALLBACK_1(HUD::onDialogOpen, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);
}

void HUD::onDialogOpen(EventCustom* event)
{
	DialogMenu::DialogOpenArgs* args = static_cast<DialogMenu::DialogOpenArgs*>(event->getUserData());

	this->dialogNode->removeAllChildren();
	this->dialogNode->addChild(args->dialogMenu);
}
