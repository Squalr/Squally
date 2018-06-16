#include "Rain.h"

const std::string Rain::KeyWeatherRain = "rain";

Rain* Rain::create(std::string name, ValueMap properties)
{
	Rain* instance = new Rain(name, properties);

	instance->autorelease();

	return instance;
}

Rain::Rain(std::string name, ValueMap properties) : SerializableLayer(name, nullptr, properties)
{
	this->rain = ParticleSystemQuad::create(Resources::Particles_Rain);
	this->rain->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->rain->start();

	this->addChild(this->rain);
}

Rain::~Rain()
{
}

void Rain::onEnter()
{
	SerializableLayer::onEnter();

	this->scheduleUpdate();
}

void Rain::update(float dt)
{
	SerializableLayer::update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = LevelCamera::getInstance()->getCameraPosition();

	this->rain->setSourcePosition(Vec2(cameraPosition.x + visibleSize.width / 2, cameraPosition.y + visibleSize.height + 64.0f));
}