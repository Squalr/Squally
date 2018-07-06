#include "Fireflies.h"

const std::string Fireflies::KeyWeatherFireflies = "fireflies";

Fireflies* Fireflies::create(ValueMap* properties, std::string name)
{
	Fireflies* instance = new Fireflies(properties, name);

	instance->autorelease();

	return instance;
}

Fireflies::Fireflies(ValueMap* properties, std::string name) : SerializableLayer(properties, name, nullptr)
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
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->fireflies->setSourcePosition(cameraPosition + visibleSize / 2);
}