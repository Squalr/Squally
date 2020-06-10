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

HealthLink* HealthLink::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	HealthLink* instance = new HealthLink(caster, target);

	instance->autorelease();

	return instance;
}

HealthLink::HealthLink(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Clones, BuffData(HealthLink::Duration, HealthLink::HealthLinkIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->healthLinkDamage = 0;

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->bubble);
	this->addChild(this->spellAura);
}

HealthLink::~HealthLink()
{
}

void HealthLink::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	this->bubble->runAction(FadeTo::create(0.25f, 255));

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));
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
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_Clones,
				HealthLinkGenericPreview::create(),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_HealthLink_RegisterEbx::create(),
					},
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Buffs_HealthLink_RegisterEdi::create(),
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
				}
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

void HealthLink::onBeforeDamageTaken(ModifyableDamageOrHealing damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->healthLinkDamage = damageOrHealing.originalDamageOrHealing;

	// Do not use the hackable code for the main target
	*damageOrHealing.damageOrHealing /= 2;

	this->applyHealthLink();

	// Damage all team mates
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
	{
		for (auto next : timeline->getSameTeamEntities(damageOrHealing.target))
		{
			if (next != damageOrHealing.target)
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(damageOrHealing.caster, next, -std::abs(this->healthLinkDamage), true));
			}
		}
	}));
}

NO_OPTIMIZE void HealthLink::applyHealthLink()
{
	static volatile int healthCopy = 0;

	healthCopy = this->healthLinkDamage;

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, healthCopy);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_UNDYING);
	ASM(shr ZAX, 1);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(healthCopy, ZAX);

	ASM(pop ZAX);

	this->healthLinkDamage = healthCopy;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
