#include "CursedSwings.h"

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
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CursedSwings/CursedSwingsGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
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

#define LOCAL_FUNC_ID_CURSED_SWINGS 1

const std::string CursedSwings::CursedSwingsIdentifier = "cursed-swings";
const float CursedSwings::Duration = -1.0f;

// Static to prevent GCC optimization issues
volatile int CursedSwings::cursedSwingsDamage = 0;

CursedSwings* CursedSwings::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	CursedSwings* instance = new CursedSwings(caster, target);

	instance->autorelease();

	return instance;
}

CursedSwings::CursedSwings(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Clones, AbilityType::Physical, BuffData(CursedSwings::Duration, CursedSwings::CursedSwingsIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->cursedSwingsDamage = 0;

	this->addChild(this->spellEffect);
}

CursedSwings::~CursedSwings()
{
}

void CursedSwings::onEnter()
{
	super::onEnter();

	this->spellEffect->start();
}

void CursedSwings::initializePositions()
{
	super::initializePositions();
}

void CursedSwings::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_CURSED_SWINGS,
			HackableCode::HackableCodeInfo(
				CursedSwings::CursedSwingsIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CursedSwings::create(),
				HackableBase::HackBarColor::Blue,
				UIResources::Menus_Icons_Clones,
				LazyNode<HackablePreview>::create([=](){ return CursedSwingsGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_RegisterEdi::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentShr::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentShrBy1::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentElaborate::create()) +
						"shr edi, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentHint::create())
						
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentShr::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentShrBy1::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentElaborate::create()) +
						"shr rdi, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentHint::create())
					),
				},
				true
			)
		},
	};

	auto func = &CursedSwings::applyCursedSwings;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

NO_OPTIMIZE void CursedSwings::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->cursedSwingsDamage = damageOrHealing->damageOrHealingValue;

	this->applyCursedSwings();

	// Damage all team mates
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		std::vector<PlatformerEntity*> targets = timeline->getSameTeamEntities(damageOrHealing->target);
		std::vector<PlatformerEntity*> cursedSwingsTargets; 
		for (PlatformerEntity* target : targets)
		{
			if (target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
				{
					entityBuffBehavior->getBuff<CursedSwings>([&](CursedSwings* cursedSwings)
					{
						cursedSwingsTargets.push_back(target);
					});
				});
			}
		}

		// For some incomprehensible reason, this needs to be a separate loop otherwise some enemies do not get it at all.
		// TODO: Figure out why, if you care enough.
		for (PlatformerEntity* target : cursedSwingsTargets)
		{
			CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(damageOrHealing->caster, target, std::abs(this->cursedSwingsDamage), AbilityType::Passive, true));
		}
	}));
}
END_NO_OPTIMIZE

NO_OPTIMIZE void CursedSwings::applyCursedSwings()
{
	static volatile int cursedSwingsDamageLocal = 0;

	cursedSwingsDamageLocal = this->cursedSwingsDamage;

	ASM_PUSH_EFLAGS()
	ASM(push ZDI);
	ASM_MOV_REG_VAR(edi, cursedSwingsDamageLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CURSED_SWINGS);
	ASM(shr ZDI, 1);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(cursedSwingsDamageLocal, edi);

	ASM(pop ZDI);
	ASM_POP_EFLAGS()

	this->cursedSwingsDamage = cursedSwingsDamageLocal;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
