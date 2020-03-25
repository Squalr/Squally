#include "Strength.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantFloat.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Strength/StrengthClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Strength/StrengthGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_HASTE 1

const std::string Strength::StrengthIdentifier = "stone-skin";

const int Strength::MaxMultiplier = 3;
const float Strength::Duration = 12.0f;

Strength* Strength::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Strength* instance = new Strength(caster, target);

	instance->autorelease();

	return instance;
}

Strength::Strength(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, BuffData(Strength::Duration, Strength::StrengthIdentifier))
{
	this->clippy = StrengthClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
}

Strength::~Strength()
{
}

void Strength::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void Strength::initializePositions()
{
	super::initializePositions();

	this->spellEffect->setPositionY(-this->target->getEntityCenterPoint().y / 2.0f);
}

void Strength::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void Strength::registerHackables()
{
	super::registerHackables();

	if (this->target == nullptr)
	{
		return;
	}

	this->clippy->setIsEnabled(false);

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HASTE,
			HackableCode::HackableCodeInfo(
				Strength::StrengthIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Strength_Strength::create(),
				UIResources::Menus_Icons_Clock,
				StrengthGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Buffs_Strength_RegisterEsi::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				this->clippy,
				{
				}
			)
		},
	};

	auto hasteFunc = &Strength::applyStrength;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void Strength::onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback)
{
	this->currentDamageDelt = *damageOrHealing;

	this->applyStrength();

	*damageOrHealing = this->currentDamageDelt;
}

NO_OPTIMIZE void Strength::applyStrength()
{
	volatile int originalDamage = this->currentDamageDelt;
	volatile int damageDelt = this->currentDamageDelt;

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, damageDelt);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(add ZAX, 4);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageDelt, ZAX);

	ASM(pop ZAX);

	// Bound multiplier in either direction
	this->currentDamageDelt = MathUtils::clamp(damageDelt, -std::abs(originalDamage) * Strength::MaxMultiplier, std::abs(originalDamage) * Strength::MaxMultiplier);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
