#include "Smoke.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/ccRandom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/CutsceneResources.h"

using namespace cocos2d;

const std::string Smoke::ScheduleKeySpawnSmoke = "SCHEDULE_SPAWN_SMOKE";

Smoke* Smoke::create(SmartNode* followTarget)
{
	Smoke* instance = new Smoke(followTarget);

	instance->autorelease();

	return instance;
}

Smoke::Smoke(SmartNode* followTarget)
{
	this->follow = followTarget;
	this->smokeAnimation = SmartAnimationSequenceNode::create(CutsceneResources::NeonCity_FlyingCars_Smoke_0000);

	this->smokeAnimation->setOpacity(0);

	this->setPosition(this->follow->getPosition());

	this->addChild(this->smokeAnimation);
}

Smoke::~Smoke()
{
	this->smokeAnimation->release();
}

void Smoke::stopFollow()
{
	this->follow = nullptr;
	this->smokeAnimation->stopAllActions();
	this->unschedule(Smoke::ScheduleKeySpawnSmoke);
}

void Smoke::onEnter()
{
	SmartNode::onEnter();

	if (this->follow != nullptr)
	{
		// Following an object -- keep making smoke forever
		this->schedule([=](float dt)
		{
			if (this->follow == nullptr)
			{
				return;
			}

			this->setPosition(this->follow->getPosition());
			this->smokeAnimation->runAction(Sequence::create(
				FadeTo::create(0.0f, 255), 
				DelayTime::create(0.1f), 
				CallFunc::create([=]()
				{
					this->smokeAnimation->playAnimation(CutsceneResources::NeonCity_FlyingCars_Smoke_0000, 0.15f);
				}),
				FadeTo::create(0.0f, 0),
				nullptr
			));
		}, 2.0f, CC_REPEAT_FOREVER, RandomHelper::random_real(0.25f, 2.0f), Smoke::ScheduleKeySpawnSmoke);
	}
	else
	{
		// Not following an object, just spawn the smoke once
		this->smokeAnimation->runAction(Sequence::create(
			FadeTo::create(0.0f, 255),
			DelayTime::create(0.1f),
			CallFunc::create([=]()
			{
				this->smokeAnimation->playAnimation(CutsceneResources::NeonCity_FlyingCars_Smoke_0000, 0.15f);
			}),
			FadeTo::create(0.0f, 0),
			nullptr
		));
	}
}
