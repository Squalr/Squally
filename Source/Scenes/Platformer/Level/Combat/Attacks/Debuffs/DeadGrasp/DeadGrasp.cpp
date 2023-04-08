#include "DeadGrasp.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/DeadGrasp/DeadGraspGenericPreview.h"
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

#define LOCAL_FUNC_ID_DEAD_GRASP 1

const std::string DeadGrasp::DeadGraspIdentifier = "dead-grasp";
const std::string DeadGrasp::HackIdentifierDeadGrasp = "dead-grasp";

const int DeadGrasp::MaxMultiplier = 4;
const float DeadGrasp::DamageIncrease = 10.0f; // Keep in sync with asm
const float DeadGrasp::Duration = 16.0f;

DeadGrasp* DeadGrasp::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	DeadGrasp* instance = new DeadGrasp(caster, target);

	instance->autorelease();

	return instance;
}

DeadGrasp::DeadGrasp(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_DeadGrasp, AbilityType::Physical, BuffData(DeadGrasp::Duration, DeadGrasp::DeadGraspIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

DeadGrasp::~DeadGrasp()
{
}

void DeadGrasp::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void DeadGrasp::initializePositions()
{
	super::initializePositions();
}

void DeadGrasp::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_DEAD_GRASP,
			HackableCode::HackableCodeInfo(
				DeadGrasp::HackIdentifierDeadGrasp,
				Strings::Menus_Hacking_Abilities_Debuffs_DeadGrasp_DeadGrasp::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_DeadGrasp,
				LazyNode<HackablePreview>::create([=](){ return DeadGraspGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_DeadGrasp_RegisterEsi::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						std::string("fild dword ptr [esi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentAbs::create()) +
						std::string("fabs\n") +
						std::string("fistp dword ptr [esi]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_DeadGrasp_CommentAbs::create())
						, // x64
						std::string("fild dword ptr [rsi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentAbs::create()) +
						std::string("fabs\n") +
						std::string("fistp dword ptr [rsi]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_DeadGrasp_CommentAbs::create())
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(DeadGrasp::applyDeadGrasp, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void DeadGrasp::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyDeadGrasp();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * DeadGrasp::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * DeadGrasp::MaxMultiplier);
}

NO_OPTIMIZE void DeadGrasp::applyDeadGrasp()
{
	static volatile int currentDamageDealtLocal = 0;
	static volatile int* currentDamageDealtLocalPtr = &currentDamageDealtLocal;

	currentDamageDealtLocal = -Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZSI, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_DEAD_GRASP);
	ASM(fild dword ptr [ZSI]);
	ASM(fabs);
	ASM(fistp dword ptr [ZSI]);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZSI);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(-currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
