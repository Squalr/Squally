#include "OceanBackground.h"

const std::string OceanBackground::KeyBackgroundOcean = "ocean";

OceanBackground* OceanBackground::create(ValueMap* properties, std::string name)
{
	OceanBackground* instance = new OceanBackground(properties, name);

	instance->autorelease();

	return instance;
}

OceanBackground::OceanBackground(ValueMap* properties, std::string name) : BackgroundBase(properties, name)
{
	this->background = Sprite::create(BackgroundResources::Platformer_Beach);

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
	SerializableLayer::update(dt);
}
