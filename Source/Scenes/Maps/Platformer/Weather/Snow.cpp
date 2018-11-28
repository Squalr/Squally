#include "Snow.h"

const std::string Snow::MapKeyWeatherLayerSnow = "snow";

Snow* Snow::create(ValueMap* properties, std::string name)
{
	Snow* instance = new Snow(properties, name);

	instance->autorelease();

	return instance;
}

Snow::Snow(ValueMap* properties, std::string name) : SerializableLayer(properties, name)
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
	SerializableLayer::onEnter();

	this->scheduleUpdate();
}

void Snow::update(float dt)
{
	SerializableLayer::update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->snow->setSourcePosition(Vec2(cameraPosition.x + visibleSize.width / 2, cameraPosition.y + visibleSize.height + 64.0f));
}