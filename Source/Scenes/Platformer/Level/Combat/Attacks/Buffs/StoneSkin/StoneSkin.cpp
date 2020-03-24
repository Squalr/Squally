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

const std::string StoneSkin::StoneSkinIdentifier = "haste";

// Note: UI sets precision on these to 1 digit
const float StoneSkin::MinSpeed = -1.0f;
const float StoneSkin::DefaultSpeed = 2.0f;
const float StoneSkin::MaxSpeed = 2.5f;
const float StoneSkin::Duration = 6.0f;

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
				Strings::Menus_Hacking_Abilities_StoneSkin_StoneSkin::create(),
				UIResources::Menus_Icons_Clock,
				StoneSkinGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_StoneSkin_RegisterEsi::create()
							->setStringReplacementVariables({ ConstantFloat::create(StoneSkin::MinSpeed, 1), ConstantFloat::create(StoneSkin::MaxSpeed, 1) })
					},
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_StoneSkin_RegisterXmm3::create()
							->setStringReplacementVariables(ConstantFloat::create(StoneSkin::DefaultSpeed, 1))
					}
				},
				int(HackFlags::None),
				this->buffData.duration,
				0.0f,
				this->clippy,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_StoneSkin_ReduceStoneSkin::create(),
						// x86
						"mov dword ptr [esi], 0.0",
						// x64
						"mov dword ptr [rsi], 0.0"
					)
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

void StoneSkin::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
	this->currentSpeed = *timelineSpeed;

	this->applyStoneSkin();

	*timelineSpeed = this->currentSpeed;
}

NO_OPTIMIZE void StoneSkin::applyStoneSkin()
{
	volatile float speedBonus = 0.0f;
	volatile float increment = StoneSkin::DefaultSpeed;
	volatile float* speedBonusPtr = &speedBonus;
	volatile float* incrementPtr = &increment;

	ASM(push ZSI);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZSI, speedBonusPtr);
	ASM_MOV_REG_VAR(ZBX, incrementPtr);
	ASM(movss xmm3, [ZBX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(movss [ZSI], xmm3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZSI);

	this->currentSpeed += MathUtils::clamp(speedBonus, StoneSkin::MinSpeed, StoneSkin::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
