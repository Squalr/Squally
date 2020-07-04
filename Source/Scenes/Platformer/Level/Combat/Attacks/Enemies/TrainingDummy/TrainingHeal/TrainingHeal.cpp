#include "TrainingHeal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
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

TrainingHeal::TrainingHeal(PlatformerEntity* caster, PlatformerEntity* target, int healAmount)
	: super(caster, target, UIResources::Menus_Icons_Heal, AbilityType::Holy, BuffData(TrainingHeal::TrainingHealIdentifier))
{
	this->healEffect = SmartAnimationSequenceNode::create();
	this->healAmount = MathUtils::clamp(healAmount, 1, 255);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);
	
	this->healEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));
	this->spellAura->setOpacity(0);

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

	this->healEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 24.0f);
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

	this->setPosition(Vec2(0.0f, 118.0f - this->owner->getEntityCenterPoint().y));
}

void TrainingHeal::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RESTORE,
			HackableCode::HackableCodeInfo(
				TrainingHeal::TrainingHealIdentifier,
				Strings::Menus_Hacking_Abilities_TrainingDummy_AddHealth::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_Heal,
				TrainingHealGenericPreview::create(),
				{
					{ HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_TrainingDummy_RegisterEdi::create() }
				},
				int(HackFlags::None),
				(float(TrainingHeal::HackTicks) * TrainingHeal::TimeBetweenTicks) + 0.1f,
				0.0f
			)
		},
	};

	auto restoreFunc = &TrainingHeal::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
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
				this->owner,
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
		TimelineEventGroup::create(timelineEvents, this, this->owner, [=]()
		{
			this->removeBuff();
		})
	));
}

NO_OPTIMIZE void TrainingHeal::runRestoreTick()
{
	static volatile int incrementAmount;

	incrementAmount = 0;

	ASM(push ZDI);
	ASM(mov ZDI, 0)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(add ZDI, 256);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(incrementAmount, edi);

	ASM(pop ZDI);

	incrementAmount = MathUtils::clamp(incrementAmount, -256, 256);

	this->healSound->play();

	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->owner, this->owner, incrementAmount, this->abilityType));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
