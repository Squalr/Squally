#include "ZombieGrasp.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/ZombieGrasp/ZombieGraspGenericPreview.h"
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

#define LOCAL_FUNC_ID_ZOMBIE_GRASP 1

const std::string ZombieGrasp::ZombieGraspIdentifier = "zombie-grasp";
const std::string ZombieGrasp::HackIdentifierZombieGrasp = "zombie-grasp";

const int ZombieGrasp::MaxMultiplier = 4;
const float ZombieGrasp::DamageIncrease = 10.0f; // Keep in sync with asm
const float ZombieGrasp::Duration = 16.0f;

ZombieGrasp* ZombieGrasp::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ZombieGrasp* instance = new ZombieGrasp(caster, target);

	instance->autorelease();

	return instance;
}

ZombieGrasp::ZombieGrasp(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ZombieGrasp, AbilityType::Physical, BuffData(ZombieGrasp::Duration, ZombieGrasp::ZombieGraspIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::MAGENTA);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

ZombieGrasp::~ZombieGrasp()
{
}

void ZombieGrasp::onEnter()
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

void ZombieGrasp::initializePositions()
{
	super::initializePositions();
}

void ZombieGrasp::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_ZOMBIE_GRASP,
			HackableCode::HackableCodeInfo(
				ZombieGrasp::HackIdentifierZombieGrasp,
				Strings::Menus_Hacking_Abilities_Debuffs_ZombieGrasp_ZombieGrasp::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ZombieGrasp,
				LazyNode<HackablePreview>::create([=](){ return ZombieGraspGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_ZombieGrasp_RegisterEdx::create(), HackableDataType::Int32, true
					},
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Debuffs_ZombieGrasp_RegisterEcx::create(), HackableDataType::Int32, true
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							ConstantString::create("fild dword ptr [edx]\n"),
							ConstantString::create("fistp dword ptr [ecx]\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()), 
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()),
							ConstantString::create("\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ZombieGrasp_CommentHint::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zcx)))
						})
						, // x64
						ConcatString::create({
							ConstantString::create("fild dword ptr [rdx]\n"),
							ConstantString::create("fistp dword ptr [rcx]\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()), 
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()),
							ConstantString::create("\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ZombieGrasp_CommentHint::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zcx)))
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(ZombieGrasp::applyZombieGrasp, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void ZombieGrasp::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyZombieGrasp();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * ZombieGrasp::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * ZombieGrasp::MaxMultiplier);
}

NO_OPTIMIZE void ZombieGrasp::applyZombieGrasp()
{
	static volatile int currentDamageDealtLocalTmp = 0;
	static volatile int* currentDamageDealtLocalTmpPtr = nullptr;
	static volatile int currentDamageDealtLocal = 0;
	static volatile int* currentDamageDealtLocalPtr  = nullptr;

	currentDamageDealtLocalTmpPtr = &currentDamageDealtLocalTmp;
	currentDamageDealtLocalPtr = &currentDamageDealtLocal;

	currentDamageDealtLocal = 0;
	currentDamageDealtLocalTmp = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt() / 4;

	ASM_PUSH_EFLAGS()
	ASM(push ZDX);
	ASM(push ZCX);

	ASM_MOV_REG_VAR(ZDX, currentDamageDealtLocalTmpPtr);
	ASM_MOV_REG_VAR(ZCX, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_ZOMBIE_GRASP);
	ASM(fild dword ptr [ZDX]);
	ASM(fistp dword ptr [ZCX]);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZCX);
	ASM(pop ZDX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
