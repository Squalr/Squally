#include "Snow.h"

const std::string Snow::KeyWeatherSnow = "snow";

Snow* Snow::create(std::string name, ValueMap properties)
{
	Snow* instance = new Snow(name, properties);

	instance->autorelease();

	return instance;
}

Snow::Snow(std::string name, ValueMap properties) : SerializableLayer(name, nullptr, properties)
{
	this->snow = ParticleSystemQuad::create(Resources::Particles_Rain);
	this->snow->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->snow->start();

	this->addChild(this->snow);
}

Snow::~Snow()
{
}

void Snow::onEnter()
{
	SerializableLayer::onEnter();

	this->scheduleUpdate();
}

void Snow::update(float dt)
{
	SerializableLayer::update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = LevelCamera::getInstance()->getCameraPosition();

	this->snow->setSourcePosition(Vec2(cameraPosition.x + visibleSize.width / 2, cameraPosition.y + visibleSize.height + 64.0f));
}