#include "SharpenedBlade.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/SharpenedBlade/SharpenedBladeGenericPreview.h"
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

#define LOCAL_FUNC_ID_FORTITUDE 1

const std::string SharpenedBlade::SharpenedBladeIdentifier = "fortitude";
const std::string SharpenedBlade::HackIdentifierSharpenedBlade = "fortitude";

const int SharpenedBlade::MaxMultiplier = 4;
const int SharpenedBlade::DamageReduction = 3; // Keep in sync with asm
const float SharpenedBlade::Duration = 12.0f;

SharpenedBlade* SharpenedBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	SharpenedBlade* instance = new SharpenedBlade(caster, target);

	instance->autorelease();

	return instance;
}

SharpenedBlade::SharpenedBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordAlt, BuffData(SharpenedBlade::Duration, SharpenedBlade::SharpenedBladeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageTaken = 0;

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->bubble);
	this->addChild(this->spellAura);
}

SharpenedBlade::~SharpenedBlade()
{
}

void SharpenedBlade::onEnter()
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

void SharpenedBlade::initializePositions()
{
	super::initializePositions();
}

void SharpenedBlade::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FORTITUDE,
			HackableCode::HackableCodeInfo(
				SharpenedBlade::HackIdentifierSharpenedBlade,
				Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_SharpenedBlade::create(),
				HackableBase::HackBarColor::Blue,
				UIResources::Menus_Icons_SwordAlt,
				SharpenedBladeGenericPreview::create(),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_RegisterEax::create(),
					},
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_SharpenedBlade_RegisterEbx::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f
			)
		},
	};

	auto func = &SharpenedBlade::applySharpenedBlade;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void SharpenedBlade::onBeforeDamageTaken(ModifyableDamageOrHealing damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->currentDamageTaken = damageOrHealing.originalDamageOrHealing;

	this->applySharpenedBlade();

	// Bound multiplier in either direction
	this->currentDamageTaken = MathUtils::clamp(this->currentDamageTaken, -std::abs(damageOrHealing.originalDamageOrHealing * SharpenedBlade::MaxMultiplier), std::abs(damageOrHealing.originalDamageOrHealing * SharpenedBlade::MaxMultiplier));
	
	*damageOrHealing.damageOrHealing = this->currentDamageTaken;
}

NO_OPTIMIZE void SharpenedBlade::applySharpenedBlade()
{
	static volatile int damageTaken;

	damageTaken = this->currentDamageTaken;

	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(ZAX, damageTaken);
	ASM_MOV_REG_VAR(ZBX, 7);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FORTITUDE);
	ASM(cmp ZAX, ZBX);
	ASM(cmovle ZAX, ZBX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageTaken, ZBX);

	ASM(pop ZBX);
	ASM(pop ZAX);

	this->currentDamageTaken = damageTaken;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
