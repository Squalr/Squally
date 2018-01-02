#include "JungleEnvironment.h"

JungleEnvironment* JungleEnvironment::create()
{
	JungleEnvironment* environment = new JungleEnvironment();

	environment->autorelease();

	return environment;
}

JungleEnvironment::JungleEnvironment()
{
	this->fireflies = ParticleSystemQuad::create(Resources::Particles_Fireflies2);
	this->fireflies->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->rain = ParticleSystemQuad::create(Resources::Particles_Rain);
	this->rain->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->addChild(this->fireflies);
	this->addChild(this->rain);

	this->scheduleUpdate();
}

JungleEnvironment::~JungleEnvironment()
{
}

void JungleEnvironment::update(float dt)
{
	Layer::update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->fireflies->setSourcePosition(LevelCamera::cameraPosition + visibleSize / 2);
	this->rain->setSourcePosition(Vec2(LevelCamera::cameraPosition.x + visibleSize.width / 2, LevelCamera::cameraPosition.y + visibleSize.height + 64.0f));
}
