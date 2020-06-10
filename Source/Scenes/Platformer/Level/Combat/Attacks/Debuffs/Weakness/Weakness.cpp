#include "Weakness.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Weakness/WeaknessGenericPreview.h"
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

#define LOCAL_FUNC_ID_STRENGTH 1

const std::string Weakness::WeaknessIdentifier = "weakness";

const int Weakness::MinMultiplier = -1;
const int Weakness::MaxMultiplier = 2;
const int Weakness::DamageIncrease = 3; // Keep in sync with asm
const float Weakness::Duration = 12.0f;

Weakness* Weakness::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Weakness* instance = new Weakness(caster, target);

	instance->autorelease();

	return instance;
}

Weakness::Weakness(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordBroken, BuffData(Weakness::Duration, Weakness::WeaknessIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageDelt = 0;

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Weakness::~Weakness()
{
}

void Weakness::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void Weakness::initializePositions()
{
	super::initializePositions();
}

void Weakness::registerHackables()
{
	super::registerHackables();

	if (this->target == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_STRENGTH,
			HackableCode::HackableCodeInfo(
				Weakness::WeaknessIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Weakness_Weakness::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_SwordBroken,
				WeaknessGenericPreview::create(),
				{
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Debuffs_Weakness_RegisterEcx::create()->setStringReplacementVariables(
							{
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(Weakness::MinMultiplier))),
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(Weakness::MaxMultiplier))),
							})
					},
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_Weakness_RegisterEcx::create()->setStringReplacementVariables(
							{
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(Weakness::MinMultiplier))),
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(Weakness::MaxMultiplier))),
							})
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f
			)
		},
	};

	auto hasteFunc = &Weakness::applyWeakness;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

NO_OPTIMIZE void Weakness::onBeforeDamageDelt(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
	super::onBeforeDamageDelt(damageOrHealing, handleCallback, caster, target);

	this->currentDamageDelt = *damageOrHealing;

	this->applyWeakness();
	
	*damageOrHealing = this->currentDamageDelt;
}
END_NO_OPTIMIZE

NO_OPTIMIZE void Weakness::applyWeakness()
{
	static volatile int originalDamage;
	static volatile int damageDelt;

	originalDamage = this->currentDamageDelt;
	damageDelt = this->currentDamageDelt;

	ASM(push ZCX);
	ASM(push ZDX);
	ASM_MOV_REG_VAR(ZCX, damageDelt);
	ASM(mov ZDX, 4);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_STRENGTH);
	ASM(cmp ZCX, ZDX);
	ASM(cmovge ZCX, ZDX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageDelt, ZCX);

	ASM(pop ZDX);
	ASM(pop ZCX);

	// Bound multiplier in either direction
	this->currentDamageDelt = MathUtils::clamp(damageDelt, -std::abs(originalDamage) * Weakness::MinMultiplier, std::abs(originalDamage) * Weakness::MaxMultiplier);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
