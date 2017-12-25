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

	this->addChild(this->healthBarFrame);
	this->addChild(this->heart);
}

HUD::~HUD()
{
}

void HUD::onEnter()
{
	Node::onEnter();

	this->InitializePositions();
}

void HUD::InitializePositions()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->healthBarFrame->setPosition(Vec2(origin.x + this->heart->getContentSize().width + this->healthBarFrame->getContentSize().width / 2, origin.y + visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
	this->heart->setPosition(Vec2(origin.x + this->heart->getContentSize().width / 2 + 16.0f, origin.y + visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
}
