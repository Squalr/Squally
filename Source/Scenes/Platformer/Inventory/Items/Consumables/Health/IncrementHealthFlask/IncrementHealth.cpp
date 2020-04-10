#include "IncrementHealth.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthClippy.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RESTORE 1

const std::string IncrementHealth::PropertyIncrementHealthTutorial = "increment-health-tutorial";
const std::string IncrementHealth::IncrementHealthIdentifier = "increment-health";
const float IncrementHealth::TimeBetweenTicks = 0.5f;
const int IncrementHealth::HackTicks = 5;
const float IncrementHealth::StartDelay = 0.15f;

IncrementHealth* IncrementHealth::create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount)
{
	IncrementHealth* instance = new IncrementHealth(caster, target, healAmount);

	instance->autorelease();

	return instance;
}

IncrementHealth::IncrementHealth(PlatformerEntity* caster, PlatformerEntity* target, int healAmount)
	: super(caster, target, UIResources::Menus_Icons_ArrowUp, BuffData())
{
	this->clippy = IncrementHealthClippy::create();
	this->healEffect = SmartAnimationSequenceNode::create(FXResources::Heal_Heal_0000);
	this->healAmount = MathUtils::clamp(healAmount, 1, 255);
	this->impactSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Ding1);
	
	this->registerClippy(this->clippy);

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

IncrementHealth::~IncrementHealth()
{
}

void IncrementHealth::onEnter()
{
	super::onEnter();

	this->runIncrementHealth();

	CombatEvents::TriggerHackableCombatCue();
}

void IncrementHealth::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f - this->target->getEntityCenterPoint().y));
}

void IncrementHealth::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void IncrementHealth::registerHackables()
{
	super::registerHackables();

	if (this->target == nullptr)
	{
		return;
	}

	this->clippy->setIsEnabled(false);

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RESTORE,
			HackableCode::HackableCodeInfo(
				IncrementHealth::IncrementHealthIdentifier,
				Strings::Menus_Hacking_Objects_IncrementHealthFlask_IncrementHealth_IncrementHealth::create(),
				UIResources::Menus_Icons_ArrowUp,
				IncrementHealthGenericPreview::create(),
				{
					{ HackableCode::Register::zdi, Strings::Menus_Hacking_Objects_IncrementHealthFlask_IncrementHealth_RegisterEdi::create() }
				},
				int(HackFlags::None),
				(float(IncrementHealth::HackTicks) * IncrementHealth::TimeBetweenTicks) + 0.1f,
				0.0f,
				this->clippy
			)
		},
	};

	auto restoreFunc = &IncrementHealth::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void IncrementHealth::runIncrementHealth()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < this->healAmount; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ArrowUp);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->target,
				icon,
				IncrementHealth::TimeBetweenTicks * float(healIndex) + IncrementHealth::StartDelay, [=]()
			{
				if (!this->healEffect->isPlayingAnimation())
				{
					this->healEffect->playAnimation(FXResources::Heal_Heal_0000, 0.05f);
				}
				
				this->runRestoreTick();
			})
		);
	}

	CombatEvents::TriggerRegisterTimelineEventGroup(CombatEvents::RegisterTimelineEventGroupArgs(
		TimelineEventGroup::create(timelineEvents, this, this->target, [=]()
		{
			this->removeBuff();
		})
	));
}

NO_OPTIMIZE void IncrementHealth::runRestoreTick()
{
	int incrementAmount = 0;

	ASM(push ZDI);
	ASM(mov ZDI, 0)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(inc ZDI);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(incrementAmount, ZDI);

	ASM(pop ZDI);

	incrementAmount = MathUtils::clamp(incrementAmount, -1, 1);

	this->healSound->play();
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->target, incrementAmount));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
