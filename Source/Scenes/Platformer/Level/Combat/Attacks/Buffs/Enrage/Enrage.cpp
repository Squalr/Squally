#include "Enrage.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantFloat.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Enrage/EnrageGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_HASTE 1

const std::string Enrage::EnrageIdentifier = "enrage";

/// TODO: Perahps this skill should be a % chance to ignore interrupt, lasting a long time. Idk.

// Note: UI sets precision on these to 1 digit
const float Enrage::MinSpeed = -1.0f;
const float Enrage::DefaultSpeed = 2.0f;
const float Enrage::MaxSpeed = 2.5f;
const float Enrage::Duration = 6.0f;

Enrage* Enrage::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Enrage* instance = new Enrage(caster, target);

	instance->autorelease();

	return instance;
}

Enrage::Enrage(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Clock, AbilityType::Physical, BuffData(Enrage::Duration, Enrage::EnrageIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Enrage);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::RED);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Enrage::~Enrage()
{
}

void Enrage::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void Enrage::initializePositions()
{
	super::initializePositions();
}

void Enrage::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HASTE,
			HackableCode::HackableCodeInfo(
				Enrage::EnrageIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Enrage_Enrage::create(),
				HackableBase::HackBarColor::Orange,
				UIResources::Menus_Icons_Clock,
				EnrageGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Buffs_Enrage_RegisterEsi::create()
							->setStringReplacementVariables({ ConstantFloat::create(Enrage::MinSpeed, 1), ConstantFloat::create(Enrage::MaxSpeed, 1) })
					},
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Buffs_Enrage_RegisterXmm3::create()
							->setStringReplacementVariables(ConstantFloat::create(Enrage::DefaultSpeed, 1))
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Buffs_Enrage_ReduceEnrage::create(),
						// x86
						"mov dword ptr [esi], 0.0",
						// x64
						"mov dword ptr [rsi], 0.0"
					)
				}
			)
		},
	};

	auto func = &Enrage::applyEnrageSpeed;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Enrage::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
	this->currentSpeed = *(speed->speed);

	this->applyEnrageSpeed();

	*(speed->speed) = this->currentSpeed;
}

void Enrage::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);
}

void Enrage::onBeforeDamageDelt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDelt(damageOrHealing);
}

NO_OPTIMIZE void Enrage::applyEnrageSpeed()
{
	volatile float speedBonus = 0.0f;
	volatile float increment = Enrage::DefaultSpeed;
	volatile float* speedBonusPtr = &speedBonus;
	volatile float* incrementPtr = &increment;

	ASM(push ZSI);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZSI, speedBonusPtr);
	ASM_MOV_REG_VAR(ZBX, incrementPtr);
	ASM(movss xmm3, [ZBX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(movss [ZSI], xmm3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZSI);

	this->currentSpeed += MathUtils::clamp(speedBonus, Enrage::MinSpeed, Enrage::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE

NO_OPTIMIZE void Enrage::applyEnrageIncreaseDamageDelt()
{
	volatile float speedBonus = 0.0f;
	volatile float increment = Enrage::DefaultSpeed;
	volatile float* speedBonusPtr = &speedBonus;
	volatile float* incrementPtr = &increment;

	ASM(push ZSI);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZSI, speedBonusPtr);
	ASM_MOV_REG_VAR(ZBX, incrementPtr);
	ASM(movss xmm3, [ZBX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(movss [ZSI], xmm3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZSI);

	this->currentSpeed += MathUtils::clamp(speedBonus, Enrage::MinSpeed, Enrage::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE

NO_OPTIMIZE void Enrage::applyEnrageIncreaseDamageTaken()
{
	volatile float speedBonus = 0.0f;
	volatile float increment = Enrage::DefaultSpeed;
	volatile float* speedBonusPtr = &speedBonus;
	volatile float* incrementPtr = &increment;

	ASM(push ZSI);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZSI, speedBonusPtr);
	ASM_MOV_REG_VAR(ZBX, incrementPtr);
	ASM(movss xmm3, [ZBX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(movss [ZSI], xmm3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZSI);

	this->currentSpeed += MathUtils::clamp(speedBonus, Enrage::MinSpeed, Enrage::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
