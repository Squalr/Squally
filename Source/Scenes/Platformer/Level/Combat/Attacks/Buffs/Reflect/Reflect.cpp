#include "Reflect.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Reflect/ReflectGenericPreview.h"
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

#define LOCAL_FUNC_ID_REFLECT 1

const std::string Reflect::ReflectIdentifier = "fortitude";

const int Reflect::MinReflect = 1;
const int Reflect::MaxMultiplier = 1;
const float Reflect::Duration = 12.0f;

Reflect* Reflect::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Reflect* instance = new Reflect(caster, target);

	instance->autorelease();

	return instance;
}

Reflect::Reflect(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldMagic, BuffData(Reflect::Duration, Reflect::ReflectIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::BLUE);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->bubble);
	this->addChild(this->spellAura);
}

Reflect::~Reflect()
{
}

void Reflect::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	this->bubble->runAction(FadeTo::create(0.25f, 255));

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void Reflect::initializePositions()
{
	super::initializePositions();
}

void Reflect::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_REFLECT,
			HackableCode::HackableCodeInfo(
				Reflect::ReflectIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Reflect_Reflect::create(),
				HackableBase::HackBarColor::Blue,
				UIResources::Menus_Icons_ShieldMagic,
				ReflectGenericPreview::create(),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_Reflect_RegisterEbx::create()->setStringReplacementVariables(
							{
								ConstantString::create(std::to_string(Reflect::MinReflect)),
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(Reflect::MaxMultiplier)))
							}),
					},
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Buffs_Reflect_RegisterEdi::create(),
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
				}
			)
		},
	};

	auto func = &Reflect::applyReflect;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Reflect::onBeforeDamageTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->damageReflected = damageOrHealing.originalDamageOrHealing;

	*damageOrHealing.damageOrHealing = 0;

	this->applyReflect();

	// Bound multiplier in either direction
	this->damageReflected = MathUtils::clamp(this->damageReflected, Reflect::MinReflect, std::abs(damageOrHealing.originalDamageOrHealing) * Reflect::MaxMultiplier);

	// Reflect damage back to caster
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(damageOrHealing.target, damageOrHealing.caster, this->damageReflected >= 0 ? -this->damageReflected : this->damageReflected, true));
}

NO_OPTIMIZE void Reflect::applyReflect()
{
	static volatile int damageTaken = 0;

	damageTaken = this->damageReflected;

	ASM(push ZSI);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZSI, damageTaken);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_REFLECT);
	ASM(mov ZBX, ZSI);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageTaken, ZBX);

	ASM(pop ZBX);
	ASM(pop ZSI);

	this->damageReflected = damageTaken;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
