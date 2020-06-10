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
	: super(caster, target, UIResources::Menus_Icons_Skull, BuffData(HealthLink::Duration, HealthLink::HealthLinkIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->newHealthHealthLink = 0;

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

	CombatEvents::TriggerHackableCombatCue();
}

void HealthLink::initializePositions()
{
	super::initializePositions();
}

void HealthLink::registerHackables()
{
	super::registerHackables();

	if (this->target == nullptr)
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
				UIResources::Menus_Icons_ShieldMagic,
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
		this->target->registerCode(next);
	}
}

void HealthLink::onBeforeDamageTaken(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
	super::onBeforeDamageTaken(damageOrHealing, handleCallback, caster, target);

	int originalHealth = target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);
	int newHealth = originalHealth - *damageOrHealing;
	this->newHealthHealthLink = newHealth;

	this->applyHealthLink();

	*damageOrHealing = (originalHealth - this->newHealthHealthLink);
}


NO_OPTIMIZE void HealthLink::applyHealthLink()
{
	static volatile int healthCopy = 0;

	healthCopy = this->newHealthHealthLink;

	ASM(push ZBX);
	ASM(push ZSI);
	ASM_MOV_REG_VAR(ZSI, healthCopy);
	ASM(mov ZBX, 1);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_UNDYING);
	ASM(cmp ZSI, 0);
	ASM(cmovle ZSI, ZBX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(healthCopy, ZSI);

	ASM(pop ZSI);
	ASM(pop ZBX);

	this->newHealthHealthLink = healthCopy;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
