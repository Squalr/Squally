#include "CardEffects.h"

#include "cocos/base/CCDirector.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Particles/SmartParticles.h"
#include "Scenes/Hexus/Config.h"

#include "Resources/ParticleResources.h"

using namespace cocos2d;

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
	this->nether = nullptr;
	this->poison = nullptr;
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
	super::onEnter();

	this->clearEffects();
}

void CardEffects::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void CardEffects::initializeListeners()
{
	super::initializeListeners();
}

void CardEffects::runEffect(CardEffect effect)
{
	this->clearEffects();

	switch (effect)
	{
		case CardEffect::Bite:
		{
			this->getBite()->start();
			break;
		}
		case CardEffect::DustPoof:
		{
			this->getDustPoof()->start();
			break;
		}
		case CardEffect::DustStorm:
		{
			this->getDustStorm()->start();
			break;
		}
		case CardEffect::FireBlast:
		{
			this->getFireBlast()->start();
			break;
		}
		case CardEffect::Flow:
		{
			this->getFlow()->start();
			break;
		}
		case CardEffect::FocusRing:
		{
			this->getFocusRing()->setVisible(true);
			this->getFocusRing()->start();
			break;
		}
		case CardEffect::FrostCirlce:
		{
			this->getFrostCircle()->start();
			break;
		}
		case CardEffect::Gush:
		{
			this->getGush()->start();
			break;
		}
		case CardEffect::Lightning:
		{
			this->getLightning()->start();
			break;
		}
		case CardEffect::MagicBurst:
		{
			this->getMagicBurst()->start();
			break;
		}
		case CardEffect::MeteorAlt:
		{
			this->getMeteorAlt()->start();
			break;
		}
		case CardEffect::MeteorBlue:
		{
			this->getMeteorBlue()->start();
			break;
		}
		case CardEffect::MeteorPurple:
		{
			this->getMeteorPurple()->start();
			break;
		}
		case CardEffect::Nether:
		{
			this->getNether()->start();
			break;
		}
		case CardEffect::Poison:
		{
			this->getPoison()->start();
			break;
		}
		case CardEffect::RadialAura:
		{
			this->getRadialAura()->start();
			break;
		}
		case CardEffect::RadialFire:
		{
			this->getRadialFire()->start();
			break;
		}
		case CardEffect::RadialGalaxy:
		{
			this->getRadialGalaxy()->start();
			break;
		}
		case CardEffect::RadialStorm:
		{
			this->getRadialStorm()->start();
			break;
		}
		case CardEffect::SelectionPulse:
		{
			this->getSelectionPulse()->setVisible(true);
			this->getSelectionPulse()->runAction(RepeatForever::create(Sequence::create(
				CallFunc::create([=]()
				{
					this->getSelectionPulse()->start();
				}),
				DelayTime::create(1.5f),
				nullptr
			)));

			break;
		}
		case CardEffect::SpinningMagic:
		{
			this->getSpinningMagic()->start();
			break;
		}
		case CardEffect::Splash:
		{
			this->getSplash()->start();
			break;
		}
		case CardEffect::StarBurst:
		{
			this->getStarBurst()->start();
			break;
		}
		case CardEffect::StarHit:
		{
			this->getStarHit()->start();
			break;
		}
		case CardEffect::TargetPulse:
		{
			this->getTargetPulse()->setVisible(true);
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
		this->getFocusRing()->stopAllActions();
		this->getFocusRing()->stop();
	}

	if (this->selectionPulse != nullptr)
	{
		this->getSelectionPulse()->setVisible(false);
		this->getSelectionPulse()->stopAllActions();
		this->getSelectionPulse()->stop();
	}

	if (this->targetPulse != nullptr)
	{
		this->getTargetPulse()->setVisible(false);
		this->getTargetPulse()->stopAllActions();
		this->getTargetPulse()->stop();
	}
}

SmartParticles* CardEffects::getBite()
{
	if (this->bite == nullptr)
	{
		this->bite = SmartParticles::create(ParticleResources::Hexus_CardEffects_Bite);

		this->bite->setGrouped();
		this->bite->stop();

		this->addChild(this->bite);
	}

	return this->bite;
}

SmartParticles* CardEffects::getDustPoof()
{
	if (this->dustPoof == nullptr)
	{
		this->dustPoof = SmartParticles::create(ParticleResources::Hexus_CardEffects_DustPoof);

		this->dustPoof->setGrouped();
		this->dustPoof->stop();

		this->addChild(this->dustPoof);
	}

	return this->dustPoof;
}

SmartParticles* CardEffects::getDustStorm()
{
	if (this->dustStorm == nullptr)
	{
		this->dustStorm = SmartParticles::create(ParticleResources::Hexus_CardEffects_DustStorm);

		this->dustStorm->setGrouped();
		this->dustStorm->stop();

		this->addChild(this->dustStorm);
	}

	return this->dustStorm;
}

SmartParticles* CardEffects::getFireBlast()
{
	if (this->fireBlast == nullptr)
	{
		this->fireBlast = SmartParticles::create(ParticleResources::Hexus_CardEffects_FireBlast);

		this->fireBlast->setGrouped();
		this->fireBlast->stop();

		this->addChild(this->fireBlast);
	}

	return this->fireBlast;
}

SmartParticles* CardEffects::getFlow()
{
	if (this->flow == nullptr)
	{
		this->flow = SmartParticles::create(ParticleResources::Hexus_CardEffects_Flow);

		this->flow->setGrouped();
		this->flow->stop();

		this->addChild(this->flow);
	}

	return this->flow;
}

SmartParticles* CardEffects::getFocusRing()
{
	if (this->focusRing == nullptr)
	{
		this->focusRing = SmartParticles::create(ParticleResources::Hexus_CardEffects_FocusRing);

		this->focusRing->setGrouped();
		this->focusRing->stop();

		// This is an infinite particle effect, needs to be hidden
		this->focusRing->setVisible(false);

		this->addChild(this->focusRing);
	}

	return this->focusRing;
}

SmartParticles* CardEffects::getFrostCircle()
{
	if (this->frostCircle == nullptr)
	{
		this->frostCircle = SmartParticles::create(ParticleResources::Hexus_CardEffects_FrostCircle);

		this->frostCircle->setGrouped();
		this->frostCircle->stop();

		this->addChild(this->frostCircle);
	}

	return this->frostCircle;
}

SmartParticles* CardEffects::getGush()
{
	if (this->gush == nullptr)
	{
		this->gush = SmartParticles::create(ParticleResources::Hexus_CardEffects_Gush);

		this->gush->setGrouped();
		this->gush->stop();

		this->addChild(this->gush);
	}

	return this->gush;
}

SmartParticles* CardEffects::getLightning()
{
	if (this->lightning == nullptr)
	{
		this->lightning = SmartParticles::create(ParticleResources::Hexus_CardEffects_Lightning);

		this->lightning->setGrouped();
		this->lightning->stop();

		this->addChild(this->lightning);
	}

	return this->lightning;
}

SmartParticles* CardEffects::getMagicBurst()
{
	if (this->magicBurst == nullptr)
	{
		this->magicBurst = SmartParticles::create(ParticleResources::Hexus_CardEffects_MagicBurst);

		this->magicBurst->setGrouped();
		this->magicBurst->stop();

		this->addChild(this->magicBurst);
	}

	return this->magicBurst;
}

SmartParticles* CardEffects::getMeteorAlt()
{
	if (this->meteorAlt == nullptr)
	{
		this->meteorAlt = SmartParticles::create(ParticleResources::Hexus_CardEffects_MeteorAlt);

		this->meteorAlt->setGrouped();
		this->meteorAlt->stop();

		this->addChild(this->meteorAlt);
	}

	return this->meteorAlt;
}

SmartParticles* CardEffects::getMeteorBlue()
{
	if (this->meteorBlue == nullptr)
	{
		this->meteorBlue = SmartParticles::create(ParticleResources::Hexus_CardEffects_MeteorBlue);

		this->meteorBlue->setGrouped();
		this->meteorBlue->stop();

		this->addChild(this->meteorBlue);
	}

	return this->meteorBlue;
}

SmartParticles* CardEffects::getMeteorPurple()
{
	if (this->meteorPurple == nullptr)
	{
		this->meteorPurple = SmartParticles::create(ParticleResources::Hexus_CardEffects_MeteorPurple);

		this->meteorPurple->setGrouped();
		this->meteorPurple->stop();

		this->addChild(this->meteorPurple);
	}

	return this->meteorPurple;
}

SmartParticles* CardEffects::getNether()
{
	if (this->nether == nullptr)
	{
		this->nether = SmartParticles::create(ParticleResources::Hexus_CardEffects_Nether);

		this->nether->setGrouped();
		this->nether->stop();

		this->addChild(this->nether);
	}

	return this->nether;
}

SmartParticles* CardEffects::getPoison()
{
	if (this->poison == nullptr)
	{
		this->poison = SmartParticles::create(ParticleResources::Hexus_CardEffects_Poison);

		this->poison->setGrouped();
		this->poison->stop();

		this->addChild(this->poison);
	}

	return this->poison;
}

SmartParticles* CardEffects::getRadialAura()
{
	if (this->radialAura == nullptr)
	{
		this->radialAura = SmartParticles::create(ParticleResources::Hexus_CardEffects_RadialAura);

		this->radialAura->setGrouped();
		this->radialAura->stop();

		this->addChild(this->radialAura);
	}

	return this->radialAura;
}

SmartParticles* CardEffects::getRadialFire()
{
	if (this->radialFire == nullptr)
	{
		this->radialFire = SmartParticles::create(ParticleResources::Hexus_CardEffects_RadialFire);

		this->radialFire->setGrouped();
		this->radialFire->stop();

		this->addChild(this->radialFire);
	}

	return this->radialFire;
}

SmartParticles* CardEffects::getRadialGalaxy()
{
	if (this->radialGalaxy == nullptr)
	{
		this->radialGalaxy = SmartParticles::create(ParticleResources::Hexus_CardEffects_RadialGalaxy);

		this->radialGalaxy->setGrouped();
		this->radialGalaxy->stop();

		this->addChild(this->radialGalaxy);
	}

	return this->radialGalaxy;
}

SmartParticles* CardEffects::getRadialStorm()
{
	if (this->radialStorm == nullptr)
	{
		this->radialStorm = SmartParticles::create(ParticleResources::Hexus_CardEffects_RadialStorm);

		this->radialStorm->setGrouped();
		this->radialStorm->stop();

		this->addChild(this->radialStorm);
	}

	return this->radialStorm;
}

SmartParticles* CardEffects::getSelectionPulse()
{
	if (this->selectionPulse == nullptr)
	{
		this->selectionPulse = SmartParticles::create(ParticleResources::Hexus_CardEffects_SelectionPulse);

		this->selectionPulse->setGrouped();
		this->selectionPulse->stop();

		this->addChild(this->selectionPulse);
	}

	return this->selectionPulse;
}

SmartParticles* CardEffects::getSpinningMagic()
{
	if (this->spinningMagic == nullptr)
	{
		this->spinningMagic = SmartParticles::create(ParticleResources::Hexus_CardEffects_SpinningMagic);

		this->spinningMagic->setGrouped();
		this->spinningMagic->stop();

		this->addChild(this->spinningMagic);
	}

	return this->spinningMagic;
}

SmartParticles* CardEffects::getSplash()
{
	if (this->splash == nullptr)
	{
		this->splash = SmartParticles::create(ParticleResources::Hexus_CardEffects_Splash);

		this->splash->setGrouped();
		this->splash->stop();

		this->addChild(this->splash);
	}

	return this->splash;
}

SmartParticles* CardEffects::getStarBurst()
{
	if (this->starBurst == nullptr)
	{
		this->starBurst = SmartParticles::create(ParticleResources::Hexus_CardEffects_StarBurst);

		this->starBurst->setGrouped();
		this->starBurst->stop();

		this->addChild(this->starBurst);
	}

	return this->starBurst;
}

SmartParticles* CardEffects::getStarHit()
{
	if (this->starHit == nullptr)
	{
		this->starHit = SmartParticles::create(ParticleResources::Hexus_CardEffects_StarHit);

		this->starHit->setGrouped();
		this->starHit->stop();

		this->addChild(this->starHit);
	}

	return this->starHit;
}

SmartParticles* CardEffects::getTargetPulse()
{
	if (this->targetPulse == nullptr)
	{
		this->targetPulse = SmartParticles::create(ParticleResources::Hexus_CardEffects_TargetPulse);

		this->targetPulse->setGrouped();
		this->targetPulse->stop();

		this->addChild(this->targetPulse);
	}

	return this->targetPulse;
}
