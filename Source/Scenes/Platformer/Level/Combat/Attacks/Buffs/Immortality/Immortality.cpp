#include "Immortality.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Immortality/ImmortalityGenericPreview.h"
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

#define LOCAL_FUNC_ID_IMMORTALITY 1

const std::string Immortality::ImmortalityIdentifier = "immortality";
const float Immortality::Duration = 120.0f;
const std::string Immortality::StateKeyImmortalityNewHealth = "ANTI_OPTIMIZE_STATE_KEY_IMMORTALITY_DAMAGE";

Immortality* Immortality::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Immortality* instance = new Immortality(caster, target);

	instance->autorelease();

	return instance;
}

Immortality::Immortality(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Skull, AbilityType::Shadow, BuffData(Immortality::Duration, Immortality::ImmortalityIdentifier, 0.0f))
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

Immortality::~Immortality()
{
}

void Immortality::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
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

void Immortality::initializePositions()
{
	super::initializePositions();
}

void Immortality::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_IMMORTALITY,
			HackableCode::HackableCodeInfo(
				Immortality::ImmortalityIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Immortality_Immortality::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_Skull,
				LazyNode<HackablePreview>::create([=](){ return ImmortalityGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Buffs_Immortality_RegisterEsi::create(),
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Immortality_CommentCompare::create()) + 
						std::string("cmp esi, 0\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Immortality_CommentJump::create()) + 
						std::string("je applyImmortality\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Immortality_CommentElse::create()) + 
						std::string("jmp skipCode\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Immortality_CommentApplyImmortality::create()) + 
						std::string("applyImmortality:\n") +
						std::string("mov esi, 1\n\n") +
						std::string("skipCode:\n\n)") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJe::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Immortality_CommentCompare::create()) + 
						std::string("cmp rsi, 0\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Immortality_CommentJump::create()) + 
						std::string("je applyImmortality\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Immortality_CommentElse::create()) + 
						std::string("jmp skipCode\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Immortality_CommentApplyImmortality::create()) + 
						std::string("applyImmortality:\n") +
						std::string("mov rsi, 1\n\n") +
						std::string("skipCode:\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJe::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create())
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Immortality::applyImmortality, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Immortality::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	if (damageOrHealing->damageOrHealingValue < 0)
	{
		return;
	}
	
	Buff::HackStateStorage[Immortality::StateKeyImmortalityNewHealth] = Value(1);

	this->applyImmortality();

	(*damageOrHealing->damageOrHealing) =  (damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0) - Buff::HackStateStorage[Immortality::StateKeyImmortalityNewHealth].asInt());
	// *(int*)(GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer()) = Buff::HackStateStorage[Immortality::StateKeyImmortalityNewHealth].asInt();
}

void Immortality::onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeHealingTaken(damageOrHealing);

	if (damageOrHealing->damageOrHealingValue > 0)
	{
		return;
	}

	Buff::HackStateStorage[Immortality::StateKeyImmortalityNewHealth] = Value(1);

	this->applyImmortality();

	(*damageOrHealing->damageOrHealing) =  (damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0) - Buff::HackStateStorage[Immortality::StateKeyImmortalityNewHealth].asInt());
	// *(int*)(GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer()) = Buff::HackStateStorage[Immortality::StateKeyImmortalityNewHealth].asInt();
}

NO_OPTIMIZE void Immortality::applyImmortality()
{
	static volatile int newHealthImmortality = 0;

	newHealthImmortality = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Immortality::StateKeyImmortalityNewHealth, Value(0)).asInt();

	ASM_PUSH_EFLAGS();
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZSI, newHealthImmortality);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_IMMORTALITY);
	ASM(cmp ZSI, 0);
	ASM(je applyImmortalityHp);
	ASM(jmp skipCodeImmortality);
	ASM(applyImmortalityHp:);
	ASM(mov ZSI, 1);
	ASM(skipCodeImmortality:);
	ASM_NOP16();
	HACKABLE_CODE_END();
		
	ASM_MOV_VAR_REG(newHealthImmortality, esi);

	ASM(pop ZSI);
	ASM_POP_EFLAGS();

	Buff::HackStateStorage[Immortality::StateKeyImmortalityNewHealth] = newHealthImmortality;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
