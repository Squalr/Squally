#include "SnowEnvironment.h"

SnowEnvironment* SnowEnvironment::create()
{
	SnowEnvironment* instance = new SnowEnvironment();

	instance->autorelease();

	return instance;
}

SnowEnvironment::SnowEnvironment()
{
	this->snow = ParticleSystemQuad::create(Resources::Particles_Rain);
	this->snow->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->addChild(this->snow);

	this->scheduleUpdate();
}

SnowEnvironment::~SnowEnvironment()
{
}

void SnowEnvironment::update(float dt)
{
	Layer::update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->snow->setSourcePosition(Vec2(LevelCamera::cameraPosition.x + visibleSize.width / 2, LevelCamera::cameraPosition.y + visibleSize.height + 64.0f));
}
