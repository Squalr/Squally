#include "UnholyBlade.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/UnholyBlade/UnholyBladeGenericPreview.h"
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

const std::string UnholyBlade::UnholyBladeIdentifier = "unholy-blade";
const std::string UnholyBlade::HackIdentifierUnholyBlade = "unholy-blade";

const int UnholyBlade::MaxMultiplier = 6;
const int UnholyBlade::DamageDelt = 1;
const float UnholyBlade::Duration = 24.0f;

UnholyBlade* UnholyBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	UnholyBlade* instance = new UnholyBlade(caster, target);

	instance->autorelease();

	return instance;
}

UnholyBlade::UnholyBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordGlowYellow, AbilityType::Nature, BuffData(UnholyBlade::Duration, UnholyBlade::UnholyBladeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

UnholyBlade::~UnholyBlade()
{
}

void UnholyBlade::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void UnholyBlade::initializePositions()
{
	super::initializePositions();
}

void UnholyBlade::registerHackables()
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
				UnholyBlade::HackIdentifierUnholyBlade,
				Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_UnholyBlade::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_SwordGlowYellow,
				LazyNode<HackablePreview>::create([=](){ return UnholyBladeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_Register::create(), true
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFldz::create()),
							ConstantString::create("fldz\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentPushDamage::create()),
							ConstantString::create("fild dword ptr [ebx]\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentCompare::create()),
							ConstantString::create("fcompp\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentConvert::create()),
							ConstantString::create("fstsw ax\n"),
							ConstantString::create("sahf\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentSkip::create()),
							ConstantString::create("jb skipCode\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentNegate::create()),
							ConstantString::create("fild dword ptr [ebx]\n"),
							ConstantString::create("fchs\n"),
							ConstantString::create("fistp dword ptr [ebx]\n\n"),
							ConstantString::create("skipCode:\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentHint1::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentHint2::create())
						})
						, // x64
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFldz::create()),
							ConstantString::create("fldz\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentPushDamage::create()),
							ConstantString::create("fild dword ptr [rbx]\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentCompare::create()),
							ConstantString::create("fcompp\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentConvert::create()),
							ConstantString::create("fstsw ax\n"),
							ConstantString::create("sahf\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentSkip::create()),
							ConstantString::create("jb skipCode\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentNegate::create()),
							ConstantString::create("fild dword ptr [rbx]\n"),
							ConstantString::create("fchs\n"),
							ConstantString::create("fistp dword ptr [rbx]\n\n"),
							ConstantString::create("skipCode:\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentHint1::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentHint2::create())
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(UnholyBlade::applyUnholyBlade, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void UnholyBlade::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyUnholyBlade();

	int min = -std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * UnholyBlade::MaxMultiplier);
	int max = std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * UnholyBlade::MaxMultiplier);

	*damageOrHealing->damageOrHealing = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	*damageOrHealing->damageOrHealingMin = min;
	*damageOrHealing->damageOrHealingMax = max;
}

NO_OPTIMIZE void UnholyBlade::applyUnholyBlade()
{
	static volatile int currentDamageDealtLocal = 0;
	static volatile int* currentDamageDealtLocalPtr = nullptr;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();
	currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	
	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(ZBX, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CURSED_BLADE);
	ASM(fldz);	// Load 0
	ASM(fild dword ptr [ZBX]); // Load damage
	ASM(fcompp);	// Compare
	ASM(fstsw ax);	// Store in AX
	ASM(sahf);		// Convert to eflags
	ASM(jb skipCodeUnholyBlade);
	ASM(fild dword ptr [ZBX]);
	ASM(fchs);
	ASM(fistp dword ptr [ZBX]);
	ASM(skipCodeUnholyBlade:);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();
	HACKABLES_STOP_SEARCH();

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
