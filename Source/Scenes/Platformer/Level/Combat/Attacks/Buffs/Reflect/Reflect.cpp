#include "Reflect.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Reflect/ReflectClippy.h"
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

Reflect::Reflect(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, BuffData(Reflect::Duration, Reflect::ReflectIdentifier))
{
	this->clippy = ReflectClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::BLUE);
	this->spellAura->setOpacity(0);
	
	this->registerClippy(this->clippy);

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

	this->bubble->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		nullptr
	));

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

void Reflect::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void Reflect::registerHackables()
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
			LOCAL_FUNC_ID_REFLECT,
			HackableCode::HackableCodeInfo(
				Reflect::ReflectIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Reflect_Reflect::create(),
				UIResources::Menus_Icons_Shield,
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
				this->clippy,
				{
				}
			)
		},
	};

	auto hasteFunc = &Reflect::applyReflect;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void Reflect::onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
	super::onBeforeDamageTaken(damageOrHealing, handleCallback, caster, target);

	this->damageReflected = *damageOrHealing;

	*damageOrHealing = 0;

	this->applyReflect();

	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(target, caster, this->damageReflected >= 0 ? -this->damageReflected : this->damageReflected));
}

NO_OPTIMIZE void Reflect::applyReflect()
{
	volatile int originalDamage = this->damageReflected;
	volatile int damageTaken = this->damageReflected;

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

	// Bound multiplier in either direction
	this->damageReflected = MathUtils::clamp(damageTaken, Reflect::MinReflect, std::abs(originalDamage) * Reflect::MaxMultiplier);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
