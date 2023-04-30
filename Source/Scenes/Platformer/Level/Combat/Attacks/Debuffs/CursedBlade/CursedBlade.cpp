#include "CursedBlade.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CursedBlade/CursedBladeGenericPreview.h"
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

#define LOCAL_FUNC_ID_CURSED_BLADE 1

const std::string CursedBlade::CursedBladeIdentifier = "cursed-blade";
const std::string CursedBlade::HackIdentifierCursedBlade = "cursed-blade";

const int CursedBlade::MaxMultiplier = 6;
const int CursedBlade::DamageDelt = 1;
const float CursedBlade::Duration = 24.0f;

CursedBlade* CursedBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	CursedBlade* instance = new CursedBlade(caster, target);

	instance->autorelease();

	return instance;
}

CursedBlade::CursedBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordGlowPurple, AbilityType::Nature, BuffData(CursedBlade::Duration, CursedBlade::CursedBladeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

CursedBlade::~CursedBlade()
{
}

void CursedBlade::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void CursedBlade::initializePositions()
{
	super::initializePositions();
}

void CursedBlade::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_CURSED_BLADE,
			HackableCode::HackableCodeInfo(
				CursedBlade::HackIdentifierCursedBlade,
				Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CursedBlade::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_SwordGlowPurple,
				LazyNode<HackablePreview>::create([=](){ return CursedBladeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_RegisterEcx::create(), true
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					/*
					ASM(repeatCursedBlade:);
					ASM(fld1); // Load 1
					ASM(fisubr dword ptr [ZCX]);
					ASM(fist dword ptr [ZCX]); // Store back to damage
					ASM(fld1); // Load 1
					ASM(fxch);
					ASM(fcompp); // Compare and pop stack twice
					ASM(fstsw ax);	// Store in AX
					ASM(sahf);		// Convert to eflags
					ASM(jae repeatCursedBlade);
					*/
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentRepeat::create(),
							ConstantString::create("repeat:\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFld1::create(),
							ConstantString::create("fld1\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentSubtract::create(),
							ConstantString::create("fisubr dword ptr [ebx]\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentStoreDamage::create(),
							ConstantString::create("fist dword ptr [ebx]\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFld1::create(),
							ConstantString::create("fld1\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentSwapDamage::create(),
							ConstantString::create("fxch st1\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentCompare::create(),
							ConstantString::create("fcompp\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentConvert::create(),
							ConstantString::create("fstsw ax\n"),
							ConstantString::create("sahf\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentA::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create(),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentJump::create(),
							ConstantString::create("jae repeat\n\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentHint::create()
						})
						, // x64
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentRepeat::create(),
							ConstantString::create("repeat:\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFld1::create(),
							ConstantString::create("fld1\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentSubtract::create(),
							ConstantString::create("fisubr dword ptr [rbx]\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentStoreDamage::create(),
							ConstantString::create("fist dword ptr [rbx]\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFld1::create(),
							ConstantString::create("fld1\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentSwapDamage::create(),
							ConstantString::create("fxch st1\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentCompare::create(),
							ConstantString::create("fcompp\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentConvert::create(),
							ConstantString::create("fstsw ax\n"),
							ConstantString::create("sahf\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentA::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create(),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentJump::create(),
							ConstantString::create("jae repeat\n\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentHint::create()
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(CursedBlade::applyCursedBlade, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void CursedBlade::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyCursedBlade();

	int min = -std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * CursedBlade::MaxMultiplier);
	int max = std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * CursedBlade::MaxMultiplier);

	*damageOrHealing->damageOrHealing = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	*damageOrHealing->damageOrHealingMin = min;
	*damageOrHealing->damageOrHealingMax = max;
}

NO_OPTIMIZE void CursedBlade::applyCursedBlade()
{
	static volatile int currentDamageDealtLocal = 0;
	static volatile int* currentDamageDealtLocalPtr = nullptr;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();
	currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	
	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZCX);

	ASM_MOV_REG_VAR(ZCX, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CURSED_BLADE);
	ASM(repeatCursedBlade:);
	ASM(fld1); // Load 1
	ASM(fisubr dword ptr [ZCX]);
	ASM(fist dword ptr [ZCX]); // Store back to damage
	ASM(fld1); // Load 1
	ASM(fxch);
	ASM(fcompp); // Compare and pop stack twice
	ASM(fstsw ax);	// Store in AX
	ASM(sahf);		// Convert to eflags
	ASM(jae repeatCursedBlade);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(pop ZCX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();
	HACKABLES_STOP_SEARCH();

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
