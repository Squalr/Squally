#include "Entwined.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Entwined/EntwinedGenericPreview.h"
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

#define LOCAL_FUNC_ID_HEALTH_LINK 1

const std::string Entwined::EntwinedIdentifier = "entwined";
const float Entwined::Duration = -1.0f;

// Static to prevent GCC optimization issues
volatile int Entwined::healthLinkDamage = 0;

Entwined* Entwined::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Entwined* instance = new Entwined(caster, target);

	instance->autorelease();

	return instance;
}

Entwined::Entwined(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Clones, AbilityType::Physical, BuffData(Entwined::Duration, Entwined::EntwinedIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->healthLinkDamage = 0;

	this->addChild(this->spellEffect);
}

Entwined::~Entwined()
{
}

void Entwined::onEnter()
{
	super::onEnter();

	this->spellEffect->start();
}

void Entwined::initializePositions()
{
	super::initializePositions();
}

void Entwined::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HEALTH_LINK,
			HackableCode::HackableCodeInfo(
				Entwined::EntwinedIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Entwined_Entwined::create(),
				HackableBase::HackBarColor::Blue,
				UIResources::Menus_Icons_Clones,
				LazyNode<HackablePreview>::create([=](){ return EntwinedGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Buffs_Entwined_RegisterEdi::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Entwined_CommentElaborate::create()) +
						"shr edi, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Entwined_CommentHint::create())
						
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Entwined_CommentElaborate::create()) +
						"shr rdi, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Entwined_CommentHint::create())
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Entwined::applyEntwined, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

NO_OPTIMIZE void Entwined::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->healthLinkDamage = damageOrHealing->damageOrHealingValue;
	
	this->applyEntwined();

	// Damage all team mates
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		std::vector<PlatformerEntity*> targets = timeline->getSameTeamEntities(damageOrHealing->target);
		std::vector<PlatformerEntity*> healthLinkTargets;
		for (PlatformerEntity* target : targets)
		{
			if (target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				caster->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
				{
					entityBuffBehavior->getBuff<Entwined>([&](Entwined* healthLink)
					{
						healthLinkTargets.push_back(target);
					});
				});
			}
		}

		// For some incomprehensible reason, this needs to be a separate loop otherwise some enemies do not get it at all.
		// TODO: Figure out why, if you care enough.
		for (PlatformerEntity* target : healthLinkTargets)
		{
			CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(damageOrHealing->caster, target, std::abs(this->healthLinkDamage), AbilityType::Passive, true));
		}
	}));
}
END_NO_OPTIMIZE

NO_OPTIMIZE void Entwined::applyEntwined()
{
	static volatile int healthLinkDamageLocal = 0;

	healthLinkDamageLocal = this->healthLinkDamage;

	ASM_PUSH_EFLAGS()
	ASM(push ZDI);
	ASM_MOV_REG_VAR(edi, healthLinkDamageLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HEALTH_LINK);
	ASM(shr ZDI, 1);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(healthLinkDamageLocal, edi);

	ASM(pop ZDI);
	ASM_POP_EFLAGS()

	this->healthLinkDamage = healthLinkDamageLocal;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
