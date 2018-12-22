#include "Rain.h"

#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

const std::string Rain::MapKeyWeatherLayerRain = "rain";

Rain* Rain::create(ValueMap* properties, std::string name)
{
	Rain* instance = new Rain(properties, name);

	instance->autorelease();

	return instance;
}

Rain::Rain(ValueMap* properties, std::string name) : SerializableLayer(properties, name)
{
	this->rain = ParticleSystemQuad::create(ParticleResources::Rain);
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
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->rain->setSourcePosition(Vec2(cameraPosition.x + visibleSize.width / 2.0f, cameraPosition.y + visibleSize.height + 64.0f));
}
