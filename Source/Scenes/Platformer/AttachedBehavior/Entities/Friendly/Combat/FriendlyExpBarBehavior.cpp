#include "FriendlyExpBarBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityEqBehavior.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FriendlyExpBarBehavior::MapKeyAttachedBehavior = "friendly-exp-bars";

FriendlyExpBarBehavior* FriendlyExpBarBehavior::create(GameObject* owner)
{
	FriendlyExpBarBehavior* instance = new FriendlyExpBarBehavior(owner);

	instance->autorelease();

	return instance;
}

FriendlyExpBarBehavior::FriendlyExpBarBehavior(GameObject* owner) : super(owner, (CollisionType)CombatCollisionType::EntityFriendly)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->deltaString = Strings::Common_PlusConstant::create();
	this->deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, deltaString);
	this->expProgressBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_ExpBarFill));
	
	// Gain text
	this->deltaLabel->setTextColor(Color4B::YELLOW);
	this->deltaLabel->enableOutline(Color4B::BLACK, 2);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->expProgressBar);
	this->addChild(this->deltaLabel);
}

FriendlyExpBarBehavior::~FriendlyExpBarBehavior()
{
}

void FriendlyExpBarBehavior::onLoad()
{
    super::onLoad();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveExp, [=](EventCustom* eventCustom)
	{
		this->giveExp();
	}));

	this->expProgressBar->setOpacity(0);
	this->deltaLabel->setOpacity(0);

	const Vec2 entityCenter = this->entity->getEntityCenterPoint();
	const float offetY =  this->entity->getEntitySize().height / 2.0f + 32.0f;

	this->deltaLabel->setPosition(entityCenter + Vec2(0.0f, offetY + 48.0f));
	this->expProgressBar->setPosition(entityCenter + Vec2(0.0f, offetY));
}

void FriendlyExpBarBehavior::giveExp()
{
	static int uuid = 0;
	int expGain = 0;
	uuid++;

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
	{
		expGain += StatsTables::getKillExp(entity);
	}), PlatformerEnemy::PlatformerEnemyTag);

	this->expProgressBar->runAction(FadeTo::create(0.25f, 255));
	this->deltaLabel->runAction(FadeTo::create(0.25f, 255));
	this->deltaString->setStringReplacementVariables(ConstantString::create(std::to_string(expGain)));

	this->entity->getAttachedBehavior<EntityEqBehavior>([=](EntityEqBehavior* eqBehavior)
	{
		float startProgress = float(eqBehavior->getEqExperience()) / float(StatsTables::getExpRequiredAtLevel(eqBehavior->getEq()));
		bool didLevelUp = eqBehavior->addEqExperience(expGain);
		float endProgress = float(eqBehavior->getEqExperience()) / float(StatsTables::getExpRequiredAtLevel(eqBehavior->getEq()));

		const float fillDuration = 1.0f;
		const int updatesPerSecond = 60;
		const float interval = fillDuration / float(updatesPerSecond);
		const int ticks = int(fillDuration * float(updatesPerSecond));
		const float delay = 0.0f;
		
		if (!didLevelUp)
		{
			const float increment = (endProgress - startProgress) / float(ticks);

			// Easy case: no level up! Just fill the bar from where it is to where it will be
			expProgressBar->setProgress(startProgress);

			expProgressBar->schedule([=](float dt)
			{
				expProgressBar->setProgress(expProgressBar->getProgress() + increment);

			}, interval, ticks, delay, "EVENT_EXP_BAR_UPDATE_EASY_" + std::to_string(uuid));
		}
		else
		{
			this->runAction(Sequence::create(
				// Phase 1: Fill from start to max
				CallFunc::create([=]()
				{
					const float increment = (1.0f - startProgress) / float(ticks);

					expProgressBar->setProgress(startProgress);

					expProgressBar->schedule([=](float dt)
					{
						expProgressBar->setProgress(expProgressBar->getProgress() + increment);

					}, interval, ticks, delay, "EVENT_EXP_BAR_UPDATE_PHASE_1_" + std::to_string(uuid));
				}),
				DelayTime::create(fillDuration + 0.1f),
				// Phase 2: Fill from 0 to end
				CallFunc::create([=]()
				{
					const float increment = endProgress / float(ticks);

					expProgressBar->schedule([=](float dt)
					{
						expProgressBar->setProgress(expProgressBar->getProgress() + increment);

					}, interval, ticks, delay, "EVENT_EXP_BAR_UPDATE_PHASE_2_" + std::to_string(uuid));
				}),
				nullptr
			));
		}
	});
}
