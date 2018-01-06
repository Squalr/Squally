#include "Monitor.h"

Monitor* Monitor::create()
{
	Monitor* warpGate = new Monitor();

	warpGate->autorelease();

	return warpGate;
}

Monitor::Monitor()
{
	this->monitorSpriteFloating = FloatingSprite::create(Resources::Ingame_Objects_Monitor, Vec2(2.0f, 24.0f), Vec2(7.0f, 7.0f));
	this->monitorParticles = ParticleSystemQuad::create(Resources::Particles_Spark);
	this->monitorParticlesBack = ParticleSystemQuad::create(Resources::Particles_Spark);

	this->monitorParticles->setPositionType(ParticleSystem::PositionType::GROUPED);
	this->monitorParticlesBack->setPositionType(ParticleSystem::PositionType::GROUPED);

	FloatingSprite* sprite = this->monitorSpriteFloating;
	ParticleSystem* particles = this->monitorParticles;
	ParticleSystem* particlesBack = this->monitorParticlesBack;

	CallFunc* triggerParticles = CallFunc::create([sprite, particles]()
	{
		particles->setSourcePosition(sprite->getPosition() + Vec2(-96.0f, -72.0f));
		particles->start();
	});

	CallFunc* triggerParticlesBack = CallFunc::create([sprite, particlesBack]()
	{
		particlesBack->setSourcePosition(sprite->getPosition() + Vec2(64.0f, 64.0f));
		particlesBack->start();
	});

	this->monitorParticles->setScale(0.25f);
	this->monitorParticles->runAction(RepeatForever::create(Sequence::create(triggerParticles, DelayTime::create(8.14f), nullptr)));

	this->monitorParticlesBack->setScale(0.7f);
	this->monitorParticlesBack->runAction(RepeatForever::create(Sequence::create(triggerParticlesBack, DelayTime::create(6.77f), nullptr)));

	this->addChild(this->monitorParticlesBack);
	this->addChild(this->monitorSpriteFloating);
	this->addChild(this->monitorParticles);
}

Monitor::~Monitor()
{
}
