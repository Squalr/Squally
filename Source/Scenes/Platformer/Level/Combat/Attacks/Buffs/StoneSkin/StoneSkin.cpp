#include "StoneSkin.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/StoneSkin/StoneSkinClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/StoneSkin/StoneSkinGenericPreview.h"
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

const std::string StoneSkin::StoneSkinIdentifier = "stone-skin";

const int StoneSkin::MaxMultiplier = 4;
const float StoneSkin::Duration = 16.0f;

StoneSkin* StoneSkin::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	StoneSkin* instance = new StoneSkin(caster, target);

	instance->autorelease();

	return instance;
}

StoneSkin::StoneSkin(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, BuffData(StoneSkin::Duration, StoneSkin::StoneSkinIdentifier))
{
	this->clippy = StoneSkinClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
}

StoneSkin::~StoneSkin()
{
}

void StoneSkin::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void StoneSkin::initializePositions()
{
	super::initializePositions();

	this->spellEffect->setPositionY(-this->target->getEntityCenterPoint().y / 2.0f);
}

void StoneSkin::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void StoneSkin::registerHackables()
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
				StoneSkin::StoneSkinIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_StoneSkin_StoneSkin::create(),
				UIResources::Menus_Icons_ShieldBroken,
				StoneSkinGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Buffs_StoneSkin_RegisterEsi::create()
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

	auto hasteFunc = &StoneSkin::applyStoneSkin;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void StoneSkin::onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback)
{
	this->currentDamageTaken = *damageOrHealing;

	this->applyStoneSkin();

	*damageOrHealing = this->currentDamageTaken;
}

NO_OPTIMIZE void StoneSkin::applyStoneSkin()
{
	volatile int originalDamage = this->currentDamageTaken;
	volatile int damageTaken = this->currentDamageTaken;

	ASM(push ZAX);
	ASM(push ZCX);
	ASM(push ZDX);
	ASM_MOV_REG_VAR(ZAX, damageTaken);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(DIV_CONVERT);
	ASM(mov ZCX, 4)
	ASM(idiv ZCX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageTaken, ZAX);

	ASM(pop ZDX);
	ASM(pop ZCX);
	ASM(pop ZAX);

	// Bound multiplier in either direction
	this->currentDamageTaken = MathUtils::clamp(damageTaken, -std::abs(originalDamage) * StoneSkin::MaxMultiplier, std::abs(originalDamage) * StoneSkin::MaxMultiplier);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
