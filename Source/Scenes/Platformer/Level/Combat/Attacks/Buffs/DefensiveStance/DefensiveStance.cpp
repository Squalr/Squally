#include "DefensiveStance.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/DefensiveStance/DefensiveStanceGenericPreview.h"
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

#define LOCAL_FUNC_ID_DEFENSIVE_STANCE 1

const std::string DefensiveStance::DefensiveStanceIdentifier = "defensive-stance";
const std::string DefensiveStance::HackIdentifierDefensiveStance = "defensive-stance";

const int DefensiveStance::MaxMultiplier = 4;
const int DefensiveStance::DamageReduction = 3; // Keep in sync with asm
const float DefensiveStance::Duration = 16.0f;

DefensiveStance* DefensiveStance::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	DefensiveStance* instance = new DefensiveStance(caster, target);

	instance->autorelease();

	return instance;
}

DefensiveStance::DefensiveStance(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldGlowRed, AbilityType::Physical, BuffData(DefensiveStance::Duration, DefensiveStance::DefensiveStanceIdentifier))
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

DefensiveStance::~DefensiveStance()
{
}

void DefensiveStance::onEnter()
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

void DefensiveStance::initializePositions()
{
	super::initializePositions();
}

void DefensiveStance::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_DEFENSIVE_STANCE,
			HackableCode::HackableCodeInfo(
				DefensiveStance::HackIdentifierDefensiveStance,
				Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_DefensiveStance::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ShieldGlowRed,
				LazyNode<HackablePreview>::create([=](){ return DefensiveStanceGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_RegisterEax::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(DefensiveStance::DamageReduction)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_CommentTryChanging::create()) + 
						"sub ebx, 3\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(DefensiveStance::DamageReduction)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_DefensiveStance_CommentTryChanging::create()) + 
						"sub rbx, 3\n"
					),
				},
				true
			)
		},
	};

	auto func = &DefensiveStance::applyDefensiveStance;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void DefensiveStance::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(damageOrHealing->damageOrHealingValue);

	this->applyDefensiveStance();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * DefensiveStance::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * DefensiveStance::MaxMultiplier);
}

NO_OPTIMIZE void DefensiveStance::applyDefensiveStance()
{
	static volatile int currentDamageTakenLocal = 0;

	currentDamageTakenLocal = Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZCX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ebx, currentDamageTakenLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_DEFENSIVE_STANCE);
	ASM(sub ZBX, 3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageTakenLocal, ebx);

	ASM(pop ZBX);
	ASM(pop ZCX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(currentDamageTakenLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
