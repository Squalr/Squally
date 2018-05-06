#include "OceanBackground.h"

OceanBackground* OceanBackground::create()
{
	OceanBackground* instance = new OceanBackground();

	instance->autorelease();

	return instance;
}

OceanBackground::OceanBackground()
{
	this->background = Sprite::create(Resources::Backgrounds_Beach);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	this->addChild(this->background);

	this->scheduleUpdate();
}

OceanBackground::~OceanBackground()
{
}

void OceanBackground::update(float dt)
{
	Layer::update(dt);
}
