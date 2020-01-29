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
	this->tickCounter = 0;

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

	this->expProgressBar->setOpacity(0);
	this->deltaLabel->setOpacity(0);

	const Vec2 entityCenter = this->entity->getEntityCenterPoint();
	const float offetY =  this->entity->getEntitySize().height / 2.0f + 32.0f;

	this->deltaLabel->setPosition(entityCenter + Vec2(0.0f, offetY + 48.0f));
	this->expProgressBar->setPosition(entityCenter + Vec2(0.0f, offetY));
}

void FriendlyExpBarBehavior::giveExp(int expGain)
{
	this->expProgressBar->runAction(FadeTo::create(0.25f, 255));
	this->deltaLabel->runAction(FadeTo::create(0.25f, 255));
	this->deltaString->setStringReplacementVariables(ConstantString::create(std::to_string(expGain)));
	
	this->entity->getAttachedBehavior<EntityEqBehavior>([=](EntityEqBehavior* eqBehavior)
	{
		const float startProgress = float(eqBehavior->getEqExperience()) / float(StatsTables::getExpRequiredAtLevel(entity));
		const bool didLevelUp = eqBehavior->addEqExperience(expGain);
		const float endProgress = float(eqBehavior->getEqExperience()) / float(StatsTables::getExpRequiredAtLevel(entity));
		
		const float StartDelay = 0.5f;
		const float FillDuration = 1.0f;
		
		if (didLevelUp)
		{
			const float RestartDelay = 1.0f;
			const float Phase1Duration = (1.0f - startProgress) * FillDuration;
			const float Phase2Duration = FillDuration - Phase1Duration;

			this->fillBar(startProgress, 1.0f, Phase1Duration, StartDelay, [=]()
			{
				this->runLevelUpEffect();
				this->fillBar(0.0f, endProgress, Phase2Duration, RestartDelay);
			});
		}
		else
		{
			this->fillBar(startProgress, endProgress, FillDuration, StartDelay);
		}
	});
}

void FriendlyExpBarBehavior::fillBar(float startProgress, float endProgress, float fillDuration, float startDelay, std::function<void()> onComplete)
{
	static int UniqueId = 0;
	UniqueId++;
	
	const int UpdatesPerSecond = 30;
	const float Interval = fillDuration / float(UpdatesPerSecond);
	const int Ticks = int(fillDuration * float(UpdatesPerSecond));
	const float Increment = (endProgress - startProgress) / float(Ticks);
	this->tickCounter = 0;

	expProgressBar->setProgress(startProgress);

	expProgressBar->schedule([=](float dt)
	{
		expProgressBar->setProgress(expProgressBar->getProgress() + Increment);

		if (onComplete != nullptr && ++this->tickCounter == Ticks)
		{
			onComplete();
		}

	}, Interval, Ticks, startDelay, "EVENT_EXP_BAR_UPDATE_" + std::to_string(UniqueId));
}

void FriendlyExpBarBehavior::runLevelUpEffect()
{
	// TODO :)
}
