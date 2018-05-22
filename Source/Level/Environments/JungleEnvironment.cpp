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

	Vec2 cameraPosition = LevelCamera::getInstance()->getCameraPosition();

	this->fireflies->setSourcePosition(cameraPosition + visibleSize / 2);
	this->rain->setSourcePosition(Vec2(cameraPosition.x + visibleSize.width / 2, cameraPosition.y + visibleSize.height + 64.0f));
}
