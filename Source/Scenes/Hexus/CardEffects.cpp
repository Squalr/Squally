#include "CardEffects.h"

CardEffects* CardEffects::create()
{
	CardEffects* instance = new CardEffects();

	instance->autorelease();

	return instance;
}

CardEffects::CardEffects()
{
	this->selectionPulse = ParticleSystemQuad::create(Resources::Particles_Hexus_SelectEffect);

	this->selectionPulse->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->addChild(this->selectionPulse);
}

CardEffects::~CardEffects()
{
}

void CardEffects::onEnter()
{
	SmartNode::onEnter();
}

void CardEffects::initializePositions()
{
	SmartNode::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void CardEffects::initializeListeners()
{
	SmartNode::initializeListeners();
}

void CardEffects::runEffect(CardEffect effect)
{
	this->clearEffects();

	switch (effect)
	{
		case CardEffect::SelectionPulse:
		{
			this->selectionPulse->runAction(RepeatForever::create(Sequence::create(
				CallFunc::create([=]()
				{
					this->selectionPulse->start();
				}),
				DelayTime::create(1.5f),
				nullptr
			)));

			break;
		}
		case CardEffect::Fire:
		{
			break;
		}
	}
}

void CardEffects::clearEffects()
{
	this->selectionPulse->stopAllActions();
}
