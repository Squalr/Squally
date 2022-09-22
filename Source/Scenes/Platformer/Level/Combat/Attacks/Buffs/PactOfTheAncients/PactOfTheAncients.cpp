#include "PactOfTheAncients.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/PactOfTheAncients/PactOfTheAncientsGenericPreview.h"
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

#define LOCAL_FUNC_ID_UNDYING 1

const std::string PactOfTheAncients::PactOfTheAncientsIdentifier = "pact-of-the-ancients";
const float PactOfTheAncients::Duration = -1.0f;

// Static to prevent GCC optimization issues
volatile int PactOfTheAncients::healthLinkDamage = 0;

PactOfTheAncients* PactOfTheAncients::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	PactOfTheAncients* instance = new PactOfTheAncients(caster, target);

	instance->autorelease();

	return instance;
}

PactOfTheAncients::PactOfTheAncients(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ChainBlade, AbilityType::Physical, BuffData(PactOfTheAncients::Duration, PactOfTheAncients::PactOfTheAncientsIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->healthLinkDamage = 0;

	this->addChild(this->spellEffect);
}

PactOfTheAncients::~PactOfTheAncients()
{
}

void PactOfTheAncients::onEnter()
{
	super::onEnter();

	this->spellEffect->start();
}

void PactOfTheAncients::initializePositions()
{
	super::initializePositions();
}

void PactOfTheAncients::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_UNDYING,
			HackableCode::HackableCodeInfo(
				PactOfTheAncients::PactOfTheAncientsIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_PactOfTheAncients_PactOfTheAncients::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ChainBlade,
				LazyNode<HackablePreview>::create([=](){ return PactOfTheAncientsGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Buffs_PactOfTheAncients_RegisterEdx::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						"push 5\n"
						"pop [edx]\n"
						, // x64
						"push 5\n"
						"pop [rdx]\n"
					),
				},
				true
			)
		},
	};

	auto func = &PactOfTheAncients::applyPactOfTheAncients;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

NO_OPTIMIZE void PactOfTheAncients::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->healthLinkDamage = damageOrHealing->damageOrHealingValue;

	this->applyPactOfTheAncients();

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
					entityBuffBehavior->getBuff<PactOfTheAncients>([&](PactOfTheAncients* healthLink)
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

NO_OPTIMIZE void PactOfTheAncients::applyPactOfTheAncients()
{
	static volatile int healthLinkDamageLocal = 0;
	static volatile int* healthLinkDamageLocalPtr = nullptr;

	healthLinkDamageLocal = this->healthLinkDamage;
	healthLinkDamageLocalPtr = &healthLinkDamageLocal;

	ASM_PUSH_EFLAGS()
	ASM(push ZDX);
	ASM_MOV_REG_PTR(ZDX, healthLinkDamageLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_UNDYING);
	ASM(push 5);
	ASM(pop [ZDX]);
	ASM_NOP16();
	HACKABLE_CODE_END();
	
	ASM(pop ZDX);
	ASM_POP_EFLAGS()

	this->healthLinkDamage = healthLinkDamageLocal;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
