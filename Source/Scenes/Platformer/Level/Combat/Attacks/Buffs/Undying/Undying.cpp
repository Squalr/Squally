#include "Undying.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Undying/UndyingGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string Undying::UndyingIdentifier = "undying";
const float Undying::Duration = 120.0f;
const std::string Undying::StateKeyUndyingHealth = "ANTI_OPTIMIZE_STATE_KEY_UNDYING_HEALTH";

Undying* Undying::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Undying* instance = new Undying(caster, target);

	instance->autorelease();

	return instance;
}

Undying::Undying(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Skull, AbilityType::Shadow, BuffData(Undying::Duration, Undying::UndyingIdentifier, 0.0f))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->bubble);
	this->addChild(this->spellAura);
}

Undying::~Undying()
{
}

void Undying::onEnter()
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

void Undying::initializePositions()
{
	super::initializePositions();
}

void Undying::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_UNDYING,
			HackableCode::HackableCodeInfo(
				Undying::UndyingIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Undying_Undying::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_Skull,
				UndyingGenericPreview::create(),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_Undying_RegisterEbx::create(),
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Buffs_Undying_RegisterEsi::create(),
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

	auto func = &Undying::applyUndying;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Undying::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	if (damageOrHealing->originalDamageOrHealing < 0)
	{
		return;
	}
	
	this->HackStateStorage[Undying::StateKeyUndyingHealth] = Value(damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0) - damageOrHealing->originalDamageOrHealing);

	this->applyUndying();

	(*damageOrHealing->damageOrHealing) = (damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0) - this->HackStateStorage[Undying::StateKeyUndyingHealth].asInt());
}

void Undying::onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeHealingTaken(damageOrHealing);

	if (damageOrHealing->originalDamageOrHealing > 0)
	{
		return;
	}

	this->HackStateStorage[Undying::StateKeyUndyingHealth] = Value(damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0) + damageOrHealing->originalDamageOrHealing);

	this->applyUndying();

	*(int*)(GameUtils::getKeyOrDefault(this->HackStateStorage, Undying::StateKeyDamageOrHealing, Value(nullptr)).asPointer()) = (damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0) - GameUtils::getKeyOrDefault(this->HackStateStorage, Undying::StateKeyUndyingHealth, Value(0)).asInt());
}

NO_OPTIMIZE void Undying::applyUndying()
{
	static volatile int newHealthUndying = 0;

	newHealthUndying = GameUtils::getKeyOrDefault(this->HackStateStorage, Undying::StateKeyUndyingHealth, Value(0)).asInt();

	ASM_PUSH_EFLAGS();
	ASM(push ZBX);
	ASM(push ZSI);

	ASM(mov ZBX, 1);
	ASM_MOV_REG_VAR(esi, newHealthUndying);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_UNDYING);
	ASM(cmp ZSI, ZBX);
	ASM(cmovle ZSI, ZBX);
	ASM_NOP16();
	HACKABLE_CODE_END();
		
	ASM_MOV_VAR_REG(newHealthUndying, esi);

	ASM(pop ZSI);
	ASM(pop ZBX);
	ASM_POP_EFLAGS();

	this->HackStateStorage[Undying::StateKeyUndyingHealth] = newHealthUndying;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
