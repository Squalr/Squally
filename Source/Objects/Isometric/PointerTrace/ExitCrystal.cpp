#include "ExitCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PointerTraceEvents.h"
#include "Entities/Isometric/PointerTrace/GridEntity.h"

#include "Resources/IsometricObjectResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string ExitCrystal::MapKeyExitCrystal = "exit-crystal";

ExitCrystal* ExitCrystal::create(ValueMap& initProperties)
{
	ExitCrystal* instance = new ExitCrystal(initProperties);

	instance->autorelease();

	return instance;
}

ExitCrystal::ExitCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->shadow = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Shadow);
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_ExitCrystal);
	this->shineFx = SmartAnimationSequenceNode::create();

	this->addChild(this->shadow);
	this->addChild(this->crystal);
	this->crystal->addChild(this->shineFx);
}

ExitCrystal::~ExitCrystal()
{
}

void ExitCrystal::onEnter()
{
	super::onEnter();

	this->crystal->runAction(RepeatForever::create(
		Sequence::create(
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 128.0f))),
			EaseSineInOut::create(MoveTo::create(4.0f, Vec2(0.0f, 96.0f))),
			nullptr
		)
	));
	this->shadow->runAction(RepeatForever::create(
		Sequence::create(
			ScaleTo::create(4.0f, 0.75f),
			ScaleTo::create(4.0f, 1.0f),
			nullptr
		)
	));
}

void ExitCrystal::initializePositions()
{
	super::initializePositions();

	this->crystal->setPosition(Vec2(0.0f, 96.0f));
	this->shineFx->setPosition(Vec2(48.0f, 64.0f));
}

void ExitCrystal::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(
		PointerTraceEvents::EventEntityMoved,
		[=](EventCustom* eventCustom)
		{
			PointerTraceEvents::PointerTraceEntityMovedArgs* args = static_cast<PointerTraceEvents::PointerTraceEntityMovedArgs*>(eventCustom->getUserData());

			if (args != nullptr && args->gridEntity != nullptr && args->gridEntity->getGridIndex() == this->getGridIndex())
			{
				args->gridEntity->interruptMovement();
				this->shineFx->playAnimation(ObjectResources::FX_Shine_Shine_0000, 0.015f, true);

				this->crystal->stopAllActions();
				this->crystal->runAction(Sequence::create(
					MoveBy::create(0.5f, Vec2(0.0f, 196.0f)),
					DelayTime::create(1.5f),
					CallFunc::create([=]()
					{
						PointerTraceEvents::TriggerVictory();
					}),
					nullptr
				));

				this->shadow->stopAllActions();
				this->shadow->runAction(ScaleTo::create(0.5f, 0.5f));
			}
		}
	));
}
