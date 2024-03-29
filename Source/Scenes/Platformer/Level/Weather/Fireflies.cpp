#include "Fireflies.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

const std::string Fireflies::MapKeyWeatherLayerFireflies = "fireflies";

Fireflies* Fireflies::create(ValueMap& properties, std::string name)
{
	Fireflies* instance = new Fireflies(properties, name);

	instance->autorelease();

	return instance;
}

Fireflies::Fireflies(ValueMap& properties, std::string name) : super(properties, name, "weather")
{
	this->fireflies = SmartParticles::create(ParticleResources::Fireflies2);
	this->fireflies->setGrouped();

	this->fireflies->start();

	this->addChild(this->fireflies);
}

Fireflies::~Fireflies()
{
}

void Fireflies::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Fireflies::update(float dt)
{
	super::update(dt);

	CSize visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->fireflies->setSourcePosition(cameraPosition + visibleSize / 2.0f);
}
