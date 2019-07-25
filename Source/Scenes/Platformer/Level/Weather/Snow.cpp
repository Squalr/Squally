#include "Snow.h"

#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

const std::string Snow::MapKeyWeatherLayerSnow = "snow";

Snow* Snow::create(ValueMap& properties, std::string name)
{
	Snow* instance = new Snow(properties, name);

	instance->autorelease();

	return instance;
}

Snow::Snow(ValueMap& properties, std::string name) : super(properties, name, "weather")
{
	this->snow = ParticleSystemQuad::create(ParticleResources::Rain);
	this->snow->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->snow->start();

	this->addChild(this->snow);
}

Snow::~Snow()
{
}

void Snow::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Snow::update(float dt)
{
	super::update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->snow->setSourcePosition(Vec2(cameraPosition.x + visibleSize.width / 2.0f, cameraPosition.y + visibleSize.height + 64.0f));
}
