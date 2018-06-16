#include "Fireflies.h"

const std::string Fireflies::KeyWeatherFireflies = "fireflies";

Fireflies* Fireflies::create(std::string name, ValueMap properties)
{
	Fireflies* instance = new Fireflies(name, properties);

	instance->autorelease();

	return instance;
}

Fireflies::Fireflies(std::string name, ValueMap properties) : SerializableLayer(name, nullptr, properties)
{
	this->fireflies = ParticleSystemQuad::create(Resources::Particles_Fireflies2);
	this->fireflies->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->fireflies->start();

	this->addChild(this->fireflies);
}

Fireflies::~Fireflies()
{
}

void Fireflies::onEnter()
{
	SerializableLayer::onEnter();

	this->scheduleUpdate();
}

void Fireflies::update(float dt)
{
	SerializableLayer::update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = LevelCamera::getInstance()->getCameraPosition();

	this->fireflies->setSourcePosition(cameraPosition + visibleSize / 2);
}