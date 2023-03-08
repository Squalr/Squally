#include "ScaldingBlade.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ScaldingBlade/ScaldingBladeGenericPreview.h"
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

#define LOCAL_FUNC_ID_SCALDING_BLADE 1

const std::string ScaldingBlade::ScaldingBladeIdentifier = "scalding-blade";
const std::string ScaldingBlade::HackIdentifierScaldingBlade = "scalding-blade";

const int ScaldingBlade::MaxMultiplier = 4;
const int ScaldingBlade::DamageReduction = 3; // Keep in sync with asm
const float ScaldingBlade::Duration = 16.0f;

ScaldingBlade* ScaldingBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ScaldingBlade* instance = new ScaldingBlade(caster, target);

	instance->autorelease();

	return instance;
}

ScaldingBlade::ScaldingBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldGlowBlue, AbilityType::Physical, BuffData(ScaldingBlade::Duration, ScaldingBlade::ScaldingBladeIdentifier))
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

ScaldingBlade::~ScaldingBlade()
{
}

void ScaldingBlade::onEnter()
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

void ScaldingBlade::initializePositions()
{
	super::initializePositions();
}

void ScaldingBlade::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_SCALDING_BLADE,
			HackableCode::HackableCodeInfo(
				ScaldingBlade::HackIdentifierScaldingBlade,
				Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_ScaldingBlade::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ShieldGlowBlue,
				LazyNode<HackablePreview>::create([=](){ return ScaldingBladeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_RegisterEax::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(ScaldingBlade::DamageReduction)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_CommentTryChanging::create()) + 
						std::string("movss xmm0, dword ptr [eax]") +
						std::string("movss xmm0, dword ptr [ebx]") +
						std::string("mulss xmm0, xmm1") +
						std::string("movss dword ptr [eax], xmm0")
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(ScaldingBlade::DamageReduction)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ScaldingBlade_CommentTryChanging::create()) + 
						std::string("movss xmm0, dword ptr [rax]") +
						std::string("movss xmm0, dword ptr [rbx]") +
						std::string("mulss xmm0, xmm1") +
						std::string("movss dword ptr [rax], xmm0")
					),
				},
				true
			)
		},
	};

	auto func = &ScaldingBlade::applyScaldingBlade;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void ScaldingBlade::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyScaldingBlade();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * ScaldingBlade::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * ScaldingBlade::MaxMultiplier);
}

NO_OPTIMIZE void ScaldingBlade::applyScaldingBlade()
{
	static volatile float currentDamageDealtLocal = 0;
	static volatile float multiplierLocal = 0;
	static volatile float* currentDamageDealtLocalPtr = nullptr;
	static volatile float* multiplierLocalPtr = nullptr;

	currentDamageDealtLocal = (float)Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	multiplierLocal = 3.0f;
	currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	multiplierLocalPtr = &multiplierLocal;

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZAX, currentDamageDealtLocal);
	ASM_MOV_REG_VAR(ZBX, multiplierLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SCALDING_BLADE);
	ASM(movss xmm0, dword ptr [ZAX]);
	ASM(movss xmm0, dword ptr [ZBX]);
	ASM(mulss xmm0, xmm1);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, ebx);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value((int)currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
