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

#include "Resources/FXResources.h"
#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string ExitCrystal::MapKey = "exit-crystal";

ExitCrystal* ExitCrystal::create(ValueMap& properties)
{
	ExitCrystal* instance = new ExitCrystal(properties);

	instance->autorelease();

	return instance;
}

ExitCrystal::ExitCrystal(ValueMap& properties) : super(properties)
{
	this->shadow = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Shadow);
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_ExitCrystal);
	this->shineFx = SmartAnimationSequenceNode::create();

	this->setZSorted(true);

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
				args->gridEntity->lockMovement();

				this->crystal->stopAllActions();
				this->crystal->runAction(Sequence::create(
					MoveBy::create(0.25f, Vec2(0.0f, 128.0f)),
					CallFunc::create([=]()
					{
						this->shineFx->playAnimation(FXResources::Shine_Shine_0000, 0.015f, true);
					}),
					DelayTime::create(0.75f),
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
