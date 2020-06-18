#include "HealthLink.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/HealthLink/HealthLinkGenericPreview.h"
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

const std::string HealthLink::HealthLinkIdentifier = "health-link";
const float HealthLink::Duration = -1.0f;

// Static to prevent GCC optimization issues
volatile int HealthLink::healthLinkDamage = 0;

HealthLink* HealthLink::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	HealthLink* instance = new HealthLink(caster, target);

	instance->autorelease();

	return instance;
}

HealthLink::HealthLink(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Clones, AbilityType::Physical, BuffData(HealthLink::Duration, HealthLink::HealthLinkIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->healthLinkDamage = 0;

	this->addChild(this->spellEffect);
}

HealthLink::~HealthLink()
{
}

void HealthLink::onEnter()
{
	super::onEnter();

	this->spellEffect->start();
}

void HealthLink::initializePositions()
{
	super::initializePositions();
}

void HealthLink::registerHackables()
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
				HealthLink::HealthLinkIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_HealthLink_HealthLink::create(),
				HackableBase::HackBarColor::Blue,
				UIResources::Menus_Icons_Clones,
				HealthLinkGenericPreview::create(),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Buffs_HealthLink_RegisterEdi::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HealthLink_CommentShr::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HealthLink_CommentShrBy1::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HealthLink_CommentElaborate::create()) +
						"shr edi, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HealthLink_CommentHint::create())
						
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HealthLink_CommentShr::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HealthLink_CommentShrBy1::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HealthLink_CommentElaborate::create()) +
						"shr rdi, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HealthLink_CommentHint::create())
					),
				},
				true
			)
		},
	};

	auto func = &HealthLink::applyHealthLink;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void HealthLink::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->healthLinkDamage = damageOrHealing->originalDamageOrHealing;

	this->applyHealthLink();

	// Damage all team mates
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		bool healthLinkTargetFound = false;

		for (auto next : timeline->getSameTeamEntities(damageOrHealing->target))
		{
			if (next != damageOrHealing->target && next->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				caster->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
				{
					entityBuffBehavior->getBuff<HealthLink>([&](HealthLink* healthLink)
					{
						healthLinkTargetFound = true;
						CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(damageOrHealing->caster, next, std::abs(this->healthLinkDamage), AbilityType::Passive, true));
					});
				});
			}
		}

		if (healthLinkTargetFound)
		{
			// Do not use the hackable code for the main target
			(*damageOrHealing->damageOrHealing) /= 2;
		}
	}));
}

NO_OPTIMIZE void HealthLink::applyHealthLink()
{
	static volatile int healthCopy = 0;

	healthCopy = this->healthLinkDamage;

	ASM(push ZDI);
	ASM_MOV_REG_VAR(ZDI, healthCopy);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_UNDYING);
	ASM(shr ZDI, 1);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(healthCopy, ZDI);

	ASM(pop ZDI);

	this->healthLinkDamage = healthCopy;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
