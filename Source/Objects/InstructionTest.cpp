#include "InstructionTest.h"

InstructionTest* InstructionTest::create()
{
	InstructionTest* warpGate = new InstructionTest();

	warpGate->autorelease();

	return warpGate;
}

InstructionTest::InstructionTest()
{
	this->isOpen = false;

	this->gateOpen = Sprite::create(Resources::Ingame_Objects_WarpGateOpen);
	this->gateClosed = Sprite::create(Resources::Ingame_Objects_WarpGateClosed);
	this->gateClosedLights = Sprite::create(Resources::Ingame_Objects_WarpGateClosedLights);
	this->gateClosedLightsNode = Node::create();
	this->gateParticles = ParticleSystemQuad::create(Resources::Particles_WarpGate);

	this->sparkParticles = ParticleSystemQuad::create(Resources::Particles_Spark);
	this->sparkParticlesBack = ParticleSystemQuad::create(Resources::Particles_Spark);

	this->sparkParticles->setPositionType(ParticleSystem::PositionType::GROUPED);
	this->sparkParticlesBack->setPositionType(ParticleSystem::PositionType::GROUPED);
	this->sparkParticles->setScale(0.7f);
	this->sparkParticlesBack->setScale(0.7f);

	this->gateParticles->setPositionType(ParticleSystem::PositionType::GROUPED);
	this->gateParticles->setPosition(Vec2(0.0f, 32.0f));

	Sprite* sprite = this->gateClosed;
	ParticleSystem* particleSystem1 = this->sparkParticles;
	ParticleSystem* particleSystem2 = this->sparkParticlesBack;

	CallFunc* triggerParticles = CallFunc::create([sprite, particleSystem1]()
	{
		Size midPoint = sprite->getContentSize() / 2;
		particleSystem1->setSourcePosition(sprite->getPosition() + Vec2(midPoint.width, midPoint.height - 128.0f));
		particleSystem1->start();
	});

	CallFunc* triggerBackParticles = CallFunc::create([sprite, particleSystem2]()
	{
		Size midPoint = sprite->getContentSize() / 2;
		particleSystem2->setSourcePosition(sprite->getPosition() + Vec2(midPoint.width + 196.0f, midPoint.height + 440.0f));
		particleSystem2->start();
	});

	this->sparkParticles->runAction(RepeatForever::create(Sequence::create(triggerParticles, DelayTime::create(5.23f), nullptr)));
	this->sparkParticlesBack->runAction(RepeatForever::create(Sequence::create(triggerBackParticles, DelayTime::create(7.44f), nullptr)));

	this->gateClosedLights->runAction(RepeatForever::create(Sequence::create(FadeOut::create(3.5f), DelayTime::create(1.0f), FadeIn::create(3.5f), DelayTime::create(1.0f), nullptr)));

	this->gateParticles->setCascadeOpacityEnabled(true);
	this->gateParticles->stopSystem();
	this->gateParticles->setOpacity(0);
	this->gateOpen->setOpacity(0);

	this->gateClosed->addChild(sparkParticlesBack);
	this->gateClosed->addChild(sparkParticles);

	this->gateClosedLightsNode->addChild(this->gateClosedLights);
	this->addChild(this->gateOpen);
	this->addChild(this->gateClosed);
	this->addChild(this->gateClosedLightsNode);
	this->addChild(this->gateParticles);
}

InstructionTest::~InstructionTest()
{
}

void InstructionTest::open()
{
	if (!this->isOpen)
	{
		this->gateOpen->runAction(FadeIn::create(0.25f));
		this->gateClosed->runAction(FadeOut::create(2.0f));
		this->gateClosedLightsNode->runAction(FadeOut::create(2.0f));
		this->gateParticles->runAction(FadeIn::create(2.0f));
		this->gateParticles->start();

		this->isOpen = true;
	}
}

void InstructionTest::close()
{
	if (this->isOpen)
	{
		this->gateOpen->runAction(FadeOut::create(2.0f));
		this->gateClosed->runAction(FadeIn::create(0.25f));
		this->gateClosedLightsNode->runAction(FadeIn::create(0.25f));
		this->gateParticles->runAction(FadeOut::create(2.0f));
		this->gateParticles->stopSystem();

		this->isOpen = false;
	}
}
