#include "TrainingHeal.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/TrainingDummy/TrainingHeal/TrainingHealClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/TrainingDummy/TrainingHeal/TrainingHealGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RESTORE 1

const std::string TrainingHeal::PropertyRestorePotionTutorial = "training-heal-tutorial";
const std::string TrainingHeal::TrainingHealIdentifier = "training-heal";
const float TrainingHeal::TimeBetweenTicks = 0.5f;
const int TrainingHeal::HackTicks = 5;
const float TrainingHeal::StartDelay = 0.15f;

TrainingHeal* TrainingHeal::create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount)
{
	TrainingHeal* instance = new TrainingHeal(caster, target, healAmount);

	instance->autorelease();

	return instance;
}

TrainingHeal::TrainingHeal(PlatformerEntity* caster, PlatformerEntity* target, int healAmount) : super(caster, target, BuffData(TrainingHeal::TrainingHealIdentifier))
{
	this->clippy = TrainingHealClippy::create();
	this->healEffect = SmartAnimationSequenceNode::create(FXResources::Heal_Heal_0000);
	this->healAmount = MathUtils::clamp(healAmount, 1, 255);
	this->healSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Ding1);
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);

	this->spellAura->setOpacity(0);
	
	this->registerClippy(this->clippy);

	this->addChild(this->healEffect);
	this->addChild(this->healSound);
	this->addChild(this->spellAura);
}

TrainingHeal::~TrainingHeal()
{
}

void TrainingHeal::onEnter()
{
	super::onEnter();

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	this->runTrainingHeal();

	CombatEvents::TriggerHackableCombatCue();
}

void TrainingHeal::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f));
}

void TrainingHeal::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void TrainingHeal::registerHackables()
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
				TrainingHeal::TrainingHealIdentifier,
				Strings::Menus_Hacking_Abilities_TrainingDummy_AddHealth::create(),
				UIResources::Menus_Icons_Heal,
				TrainingHealGenericPreview::create(),
				{
					{ HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_TrainingDummy_RegisterEdi::create() }
				},
				int(HackFlags::None),
				(float(TrainingHeal::HackTicks) * TrainingHeal::TimeBetweenTicks) + 0.1f,
				0.0f,
				this->clippy
			)
		},
	};

	auto restoreFunc = &TrainingHeal::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void TrainingHeal::runTrainingHeal()
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < this->healAmount; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_Heal);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->target,
				icon,
				TrainingHeal::TimeBetweenTicks * float(healIndex) + TrainingHeal::StartDelay, [=]()
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

NO_OPTIMIZE void TrainingHeal::runRestoreTick()
{
	int incrementAmount = 0;

	ASM(push ZDI);
	ASM(mov ZDI, 0)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(add ZDI, 256);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(incrementAmount, ZDI);

	ASM(pop ZDI);

	incrementAmount = MathUtils::clamp(incrementAmount, -256, 256);

	this->healSound->play();
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->target, incrementAmount));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
