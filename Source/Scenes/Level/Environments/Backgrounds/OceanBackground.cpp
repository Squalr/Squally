#include "OceanBackground.h"

const std::string OceanBackground::KeyBackgroundOcean = "ocean";

OceanBackground* OceanBackground::create(std::string name, ValueMap properties)
{
	OceanBackground* instance = new OceanBackground(name, properties);

	instance->autorelease();

	return instance;
}

OceanBackground::OceanBackground(std::string name, ValueMap properties) : BackgroundBase(name, properties)
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
	SerializableLayer::update(dt);
}
