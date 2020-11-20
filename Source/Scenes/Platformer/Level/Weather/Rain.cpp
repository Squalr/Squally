#include "Rain.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Particles/SmartParticles.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

const std::string Rain::MapKeyWeatherLayerRain = "rain";

Rain* Rain::create(ValueMap& properties, std::string name)
{
	Rain* instance = new Rain(properties, name);

	instance->autorelease();

	return instance;
}

Rain::Rain(ValueMap& properties, std::string name) : super(properties, name, "weather")
{
	this->rain = SmartParticles::create(ParticleResources::Rain);
	this->rain->setGrouped();

	this->rain->start();

	this->addChild(this->rain);
}

Rain::~Rain()
{
}

void Rain::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Rain::update(float dt)
{
	super::update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->rain->setSourcePosition(Vec2(cameraPosition.x + visibleSize.width / 2.0f, cameraPosition.y + visibleSize.height + 64.0f));
}
