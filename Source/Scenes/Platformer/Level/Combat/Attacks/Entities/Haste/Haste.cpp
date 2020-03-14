#include "Haste.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Haste/HasteClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Haste/HasteGenericPreview.h"
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

const std::string Haste::HasteIdentifier = "haste";
const float Haste::TimeBetweenTicks = 0.5f;
const int Haste::HackTicks = 5;
const float Haste::StartDelay = 0.15f;

Haste* Haste::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Haste* instance = new Haste(caster, target);

	instance->autorelease();

	return instance;
}

Haste::Haste(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, BuffData(5.0f, Haste::HasteIdentifier))
{
	this->clippy = HasteClippy::create();
	this->spellEffect = SmartAnimationSequenceNode::create(FXResources::Restore_Restore_0000);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
}

Haste::~Haste()
{
}

void Haste::onEnter()
{
	super::onEnter();

	this->spellEffect->playAnimationRepeat(FXResources::Restore_Restore_0000, 0.05f, 0.0f, true);

	CombatEvents::TriggerHackableCombatCue();
}

void Haste::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f));
}

void Haste::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void Haste::registerHackables()
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
				Haste::HasteIdentifier,
				Strings::Menus_Hacking_Abilities_Entities_TrainingDummy_AddHealth::create(),
				UIResources::Menus_Icons_Clock,
				HasteGenericPreview::create(),
				{
					{ HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Entities_TrainingDummy_RegisterEdi::create() }
				},
				int(HackFlags::None),
				(float(Haste::HackTicks) * Haste::TimeBetweenTicks) + 0.1f,
				0.0f,
				this->clippy
			)
		},
	};

	auto hasteFunc = &Haste::applyHaste;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void Haste::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
	*timelineSpeed = this->applyHaste(*timelineSpeed);
}

NO_OPTIMIZE float Haste::applyHaste(float currentSpeed)
{
	return currentSpeed + 0.25f;

	/*
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
	*/
	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
