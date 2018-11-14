#include "CardEffects.h"

CardEffects* CardEffects::create()
{
	CardEffects* instance = new CardEffects();

	instance->autorelease();

	return instance;
}

CardEffects::CardEffects()
{
	this->bite = nullptr;
	this->dustPoof = nullptr;
	this->dustStorm = nullptr;
	this->fireBlast = nullptr;
	this->flow = nullptr;
	this->focusRing = nullptr;
	this->frostCircle = nullptr;
	this->gush = nullptr;
	this->lightning = nullptr;
	this->magicBurst = nullptr;
	this->meteorAlt = nullptr;
	this->meteorBlue = nullptr;
	this->meteorPurple = nullptr;
	this->radialAura = nullptr;
	this->radialFire = nullptr;
	this->radialGalaxy = nullptr;
	this->radialStorm = nullptr;
	this->selectionPulse = nullptr;
	this->spinningMagic = nullptr;
	this->splash = nullptr;
	this->starBurst = nullptr;
	this->starHit = nullptr;
	this->targetPulse = nullptr;
}

CardEffects::~CardEffects()
{
}

void CardEffects::onEnter()
{
	SmartNode::onEnter();

	this->clearEffects();
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
		case CardEffect::Bite:
		{
			this->getBite()->resumeEmissions();
			this->getBite()->start();
			break;
		}
		case CardEffect::DustPoof:
		{
			this->getDustPoof()->resumeEmissions();
			this->getDustPoof()->start();
			break;
		}
		case CardEffect::DustStorm:
		{
			this->getDustStorm()->resumeEmissions();
			this->getDustStorm()->start();
			break;
		}
		case CardEffect::FireBlast:
		{
			this->getFireBlast()->resumeEmissions();
			this->getFireBlast()->start();
			break;
		}
		case CardEffect::Flow:
		{
			this->getFlow()->resumeEmissions();
			this->getFlow()->start();
			break;
		}
		case CardEffect::FocusRing:
		{
			this->getFocusRing()->resumeEmissions();
			this->getFocusRing()->setVisible(true);
			break;
		}
		case CardEffect::FrostCirlce:
		{
			this->getFrostCircle()->resumeEmissions();
			this->getFrostCircle()->start();
			break;
		}
		case CardEffect::Gush:
		{
			this->getGush()->resumeEmissions();
			this->getGush()->start();
			break;
		}
		case CardEffect::Lightning:
		{
			this->getLightning()->resumeEmissions();
			this->getLightning()->start();
			break;
		}
		case CardEffect::MagicBurst:
		{
			this->getMagicBurst()->resumeEmissions();
			this->getMagicBurst()->start();
			break;
		}
		case CardEffect::MeteorAlt:
		{
			this->getMeteorAlt()->resumeEmissions();
			this->getMeteorAlt()->start();
			break;
		}
		case CardEffect::MeteorBlue:
		{
			this->getMeteorBlue()->resumeEmissions();
			this->getMeteorBlue()->start();
			break;
		}
		case CardEffect::MeteorPurple:
		{
			this->getMeteorPurple()->resumeEmissions();
			this->getMeteorPurple()->start();
			break;
		}
		case CardEffect::RadialAura:
		{
			this->getRadialAura()->resumeEmissions();
			this->getRadialAura()->start();
			break;
		}
		case CardEffect::RadialFire:
		{
			this->getRadialFire()->resumeEmissions();
			this->getRadialFire()->start();
			break;
		}
		case CardEffect::RadialGalaxy:
		{
			this->getRadialGalaxy()->resumeEmissions();
			this->getRadialGalaxy()->start();
			break;
		}
		case CardEffect::RadialStorm:
		{
			this->getRadialStorm()->resumeEmissions();
			this->getRadialStorm()->start();
			break;
		}
		case CardEffect::SelectionPulse:
		{
			this->getSelectionPulse()->runAction(RepeatForever::create(Sequence::create(
				CallFunc::create([=]()
				{
					this->getSelectionPulse()->resumeEmissions();
					this->getSelectionPulse()->start();
				}),
				DelayTime::create(1.5f),
				nullptr
			)));

			break;
		}
		case CardEffect::SpinningMagic:
		{
			this->getSpinningMagic()->resumeEmissions();
			this->getSpinningMagic()->start();
			break;
		}
		case CardEffect::Splash:
		{
			this->getSplash()->resumeEmissions();
			this->getSplash()->start();
			break;
		}
		case CardEffect::StarBurst:
		{
			this->getStarBurst()->resumeEmissions();
			this->getStarBurst()->start();
			break;
		}
		case CardEffect::StarHit:
		{
			this->getStarHit()->resumeEmissions();
			this->getStarHit()->start();
			break;
		}
		case CardEffect::TargetPulse:
		{
			this->getTargetPulse()->resumeEmissions();
			this->getTargetPulse()->start();

			break;
		}
		default:
		{
			break;
		}
	}
}

void CardEffects::clearEffects()
{
	if (this->focusRing != nullptr)
	{
		this->getFocusRing()->setVisible(false);
	}

	if (this->selectionPulse != nullptr)
	{
		this->getSelectionPulse()->stopAllActions();
	}

	if (this->targetPulse != nullptr)
	{
		this->getTargetPulse()->stopAllActions();
	}
}

ParticleSystemQuad* CardEffects::getBite()
{
	if (this->bite == nullptr)
	{
		this->bite = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_Bite);

		this->bite->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->bite->pauseEmissions();

		this->addChild(this->bite);
	}

	return this->bite;
}

ParticleSystemQuad* CardEffects::getDustPoof()
{
	if (this->dustPoof == nullptr)
	{
		this->dustPoof = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_DustPoof);

		this->dustPoof->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->dustPoof->pauseEmissions();

		this->addChild(this->dustPoof);
	}

	return this->dustPoof;
}

ParticleSystemQuad* CardEffects::getDustStorm()
{
	if (this->dustStorm == nullptr)
	{
		this->dustStorm = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_DustStorm);

		this->dustStorm->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->dustStorm->pauseEmissions();

		this->addChild(this->dustStorm);
	}

	return this->dustStorm;
}

ParticleSystemQuad* CardEffects::getFireBlast()
{
	if (this->fireBlast == nullptr)
	{
		this->fireBlast = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_FireBlast);

		this->fireBlast->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->fireBlast->pauseEmissions();

		this->addChild(this->fireBlast);
	}

	return this->fireBlast;
}

ParticleSystemQuad* CardEffects::getFlow()
{
	if (this->flow == nullptr)
	{
		this->flow = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_Flow);

		this->flow->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->flow->pauseEmissions();

		this->addChild(this->flow);
	}

	return this->flow;
}

ParticleSystemQuad* CardEffects::getFocusRing()
{
	if (this->focusRing == nullptr)
	{
		this->focusRing = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_FocusRing);

		this->focusRing->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->focusRing->pauseEmissions();

		// This is an infinite particle effect, needs to be hidden
		this->focusRing->setVisible(false);

		this->addChild(this->focusRing);
	}

	return this->focusRing;
}

ParticleSystemQuad* CardEffects::getFrostCircle()
{
	if (this->frostCircle == nullptr)
	{
		this->frostCircle = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_FrostCircle);

		this->frostCircle->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->frostCircle->pauseEmissions();

		this->addChild(this->frostCircle);
	}

	return this->frostCircle;
}

ParticleSystemQuad* CardEffects::getGush()
{
	if (this->gush == nullptr)
	{
		this->gush = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_Gush);

		this->gush->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->gush->pauseEmissions();

		this->addChild(this->gush);
	}

	return this->gush;
}

ParticleSystemQuad* CardEffects::getLightning()
{
	if (this->lightning == nullptr)
	{
		this->lightning = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_Lightning);

		this->lightning->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->lightning->pauseEmissions();

		this->addChild(this->lightning);
	}

	return this->lightning;
}

ParticleSystemQuad* CardEffects::getMagicBurst()
{
	if (this->magicBurst == nullptr)
	{
		this->magicBurst = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_MagicBurst);

		this->magicBurst->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->magicBurst->pauseEmissions();

		this->addChild(this->magicBurst);
	}

	return this->magicBurst;
}

ParticleSystemQuad* CardEffects::getMeteorAlt()
{
	if (this->meteorAlt == nullptr)
	{
		this->meteorAlt = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_MeteorAlt);

		this->meteorAlt->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->meteorAlt->pauseEmissions();

		this->addChild(this->meteorAlt);
	}

	return this->meteorAlt;
}

ParticleSystemQuad* CardEffects::getMeteorBlue()
{
	if (this->meteorBlue == nullptr)
	{
		this->meteorBlue = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_MeteorBlue);

		this->meteorBlue->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->meteorBlue->pauseEmissions();

		this->addChild(this->meteorBlue);
	}

	return this->meteorBlue;
}

ParticleSystemQuad* CardEffects::getMeteorPurple()
{
	if (this->meteorPurple == nullptr)
	{
		this->meteorPurple = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_MeteorPurple);

		this->meteorPurple->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->meteorPurple->pauseEmissions();

		this->addChild(this->meteorPurple);
	}

	return this->meteorPurple;
}

ParticleSystemQuad* CardEffects::getRadialAura()
{
	if (this->radialAura == nullptr)
	{
		this->radialAura = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_RadialAura);

		this->radialAura->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->radialAura->pauseEmissions();

		this->addChild(this->radialAura);
	}

	return this->radialAura;
}

ParticleSystemQuad* CardEffects::getRadialFire()
{
	if (this->radialFire == nullptr)
	{
		this->radialFire = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_RadialFire);

		this->radialFire->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->radialFire->pauseEmissions();

		this->addChild(this->radialFire);
	}

	return this->radialFire;
}

ParticleSystemQuad* CardEffects::getRadialGalaxy()
{
	if (this->radialGalaxy == nullptr)
	{
		this->radialGalaxy = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_RadialGalaxy);

		this->radialGalaxy->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->radialGalaxy->pauseEmissions();

		this->addChild(this->radialGalaxy);
	}

	return this->radialGalaxy;
}

ParticleSystemQuad* CardEffects::getRadialStorm()
{
	if (this->radialStorm == nullptr)
	{
		this->radialStorm = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_RadialStorm);

		this->radialStorm->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->radialStorm->pauseEmissions();

		this->addChild(this->radialStorm);
	}

	return this->radialStorm;
}

ParticleSystemQuad* CardEffects::getSelectionPulse()
{
	if (this->selectionPulse == nullptr)
	{
		this->selectionPulse = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_SelectionPulse);

		this->selectionPulse->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->selectionPulse->pauseEmissions();

		this->addChild(this->selectionPulse);
	}

	return this->selectionPulse;
}

ParticleSystemQuad* CardEffects::getSpinningMagic()
{
	if (this->spinningMagic == nullptr)
	{
		this->spinningMagic = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_SpinningMagic);

		this->spinningMagic->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->spinningMagic->pauseEmissions();

		this->addChild(this->spinningMagic);
	}

	return this->spinningMagic;
}

ParticleSystemQuad* CardEffects::getSplash()
{
	if (this->splash == nullptr)
	{
		this->splash = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_Splash);

		this->splash->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->splash->pauseEmissions();

		this->addChild(this->splash);
	}

	return this->splash;
}

ParticleSystemQuad* CardEffects::getStarBurst()
{
	if (this->starBurst == nullptr)
	{
		this->starBurst = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_StarBurst);

		this->starBurst->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->starBurst->pauseEmissions();

		this->addChild(this->starBurst);
	}

	return this->starBurst;
}

ParticleSystemQuad* CardEffects::getStarHit()
{
	if (this->starHit == nullptr)
	{
		this->starHit = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_StarHit);

		this->starHit->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->starHit->pauseEmissions();

		this->addChild(this->starHit);
	}

	return this->starHit;
}

ParticleSystemQuad* CardEffects::getTargetPulse()
{
	if (this->targetPulse == nullptr)
	{
		this->targetPulse = ParticleSystemQuad::create(Resources::Particles_Hexus_CardEffects_TargetPulse);

		this->targetPulse->setPositionType(ParticleSystem::PositionType::GROUPED);
		this->targetPulse->pauseEmissions();

		this->addChild(this->targetPulse);
	}

	return this->targetPulse;
}
