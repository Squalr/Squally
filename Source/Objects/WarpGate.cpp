#include "WarpGate.h"

WarpGate* WarpGate::create()
{
	WarpGate* warpGate = new WarpGate();

	warpGate->autorelease();

	return warpGate;
}

WarpGate::WarpGate()
{
	this->isOpen = false;

	this->gateOpen = Sprite::create(Resources::Ingame_Objects_WarpGateOpen);
	this->gateClosed = Sprite::create(Resources::Ingame_Objects_WarpGateClosed);
	this->gateParticles = ParticleSystemQuad::create(Resources::Particles_WarpGate);

	this->gateParticles->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->gateParticles->setPosition(Vec2(0.0f, 32.0f));

	this->gateParticles->setCascadeOpacityEnabled(true);
	this->gateParticles->stopSystem();
	this->gateParticles->setOpacity(0);
	this->gateOpen->setOpacity(0);

	this->addChild(this->gateOpen);
	this->addChild(this->gateClosed);
	this->addChild(this->gateParticles);
}

WarpGate::~WarpGate()
{
}

void WarpGate::open()
{
	if (!this->isOpen)
	{
		this->gateOpen->runAction(FadeIn::create(0.25f));
		this->gateClosed->runAction(FadeOut::create(2.0f));
		this->gateParticles->runAction(FadeIn::create(2.0f));
		this->gateParticles->start();

		this->isOpen = true;
	}
}

void WarpGate::close()
{
	if (this->isOpen)
	{
		this->gateOpen->runAction(FadeOut::create(2.0f));
		this->gateClosed->runAction(FadeIn::create(0.25f));
		this->gateParticles->runAction(FadeOut::create(2.0f));
		this->gateParticles->stopSystem();

		this->isOpen = false;
	}
}
