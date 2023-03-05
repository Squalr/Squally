#include "UnholyBlade.h"

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

#define LOCAL_FUNC_ID_UNHOLY_BLADE 1

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
	: super(caster, target, UIResources::Menus_Icons_SwordGlowYellow, AbilityType::Shadow, BuffData(UnholyBlade::Duration, UnholyBlade::UnholyBladeIdentifier))
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
			LOCAL_FUNC_ID_UNHOLY_BLADE,
			HackableCode::HackableCodeInfo(
				UnholyBlade::HackIdentifierUnholyBlade,
				Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_UnholyBlade::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_SwordGlowYellow,
				LazyNode<HackablePreview>::create([=](){ return UnholyBladeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_Register::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentCompare::create()) +
						"cmp edx, 0:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentJump::create()) +
						"jl doNothing\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentConvertToHealing::create()) +
						"mov ecx, edx\n" +
						"imul ecx, -1\n\n" +
						"doNothing:\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentCompare::create()) +
						"cmp rdx, 0:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentJump::create()) +
						"jl doNothing\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_UnholyBlade_CommentConvertToHealing::create()) +
						"mov rcx, rdx\n" +
						"imul rcx, -1\n\n" +
						"doNothing:\n"
					),
				},
				true
			)
		},
	};

	auto func = &UnholyBlade::applyUnholyBlade;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void UnholyBlade::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(UnholyBlade::DamageDelt);

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
	static volatile int healingLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	// TODO: Another register to store the amount healed on damage

	ASM_PUSH_EFLAGS()
	ASM(push ZDX);
	ASM(push ZCX);

	ASM(MOV ZDX, 0)
	ASM_MOV_REG_VAR(edx, currentDamageDealtLocal);

	// f([i,u])com(p)(p) + fstsw ax + sahf
	// ftst (Compares St(0) to 0.0)
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_UNHOLY_BLADE);
	ASM(cmp ZDX, 0);
	ASM(jl skipCodeUnholyBlade);
	ASM(mov ZCX, ZDX);
	ASM(imul ZCX, -1);
	ASM(skipCodeUnholyBlade:);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(healingLocal, ecx);

	ASM(pop ZCX);
	ASM(pop ZDX);
	ASM_POP_EFLAGS()

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	int max = currentDamageDealtLocal * UnholyBlade::MaxMultiplier;
	bool overflowedMin = healingLocal >= max;
	bool overflowedMax = healingLocal <= max;
	healingLocal = MathUtils::clamp(healingLocal, -max, max);
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, healingLocal, this->abilityType, true, overflowedMin, overflowedMax));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
