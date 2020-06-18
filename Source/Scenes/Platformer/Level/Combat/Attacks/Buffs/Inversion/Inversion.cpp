#include "Inversion.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantFloat.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Inversion/InversionGenericPreview.h"
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

#define LOCAL_FUNC_ID_INVERSION 1

const std::string Inversion::InversionIdentifier = "inversion";

const int Inversion::MaxMultiplier = 4;
const float Inversion::Duration = 16.0f;

Inversion* Inversion::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Inversion* instance = new Inversion(caster, target);

	instance->autorelease();

	return instance;
}

Inversion::Inversion(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_YinYang, AbilityType::Shadow, BuffData(Inversion::Duration, Inversion::InversionIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Gray);
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

Inversion::~Inversion()
{
}

void Inversion::onEnter()
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

void Inversion::initializePositions()
{
	super::initializePositions();
}

void Inversion::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_INVERSION,
			HackableCode::HackableCodeInfo(
				Inversion::InversionIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Inversion_Inversion::create(),
				HackableBase::HackBarColor::Gray,
				UIResources::Menus_Icons_YinYang,
				InversionGenericPreview::create(),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_Inversion_RegisterEax::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f
			)
		},
	};

	auto stoneSkinFunc = &Inversion::applyInversion;
	this->hackables = HackableCode::create((void*&)stoneSkinFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Inversion::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->currentDamageTaken = damageOrHealing->originalDamageOrHealing;

	this->applyInversion();

	// Bound multiplier in either direction
	this->currentDamageTaken = MathUtils::clamp(this->currentDamageTaken, -std::abs(damageOrHealing->originalDamageOrHealing * Inversion::MaxMultiplier), std::abs(damageOrHealing->originalDamageOrHealing * Inversion::MaxMultiplier));

	(*damageOrHealing->damageOrHealing) = this->currentDamageTaken;
}

NO_OPTIMIZE void Inversion::applyInversion()
{
	static volatile int damageTaken = 0;

	damageTaken = this->currentDamageTaken;

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, damageTaken);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INVERSION);
	ASM(neg ZAX)
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageTaken, ZAX);
	
	ASM(pop ZAX);

	this->currentDamageTaken = damageTaken;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
