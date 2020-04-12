#include "SiphonLife.h"

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
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/SiphonLife/SiphonLifeClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/SiphonLife/SiphonLifeGenericPreview.h"
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

#define LOCAL_FUNC_ID_HASTE 1

const std::string SiphonLife::SiphonLifeIdentifier = "haste";

// Note: UI sets precision on these to 1 digit
const float SiphonLife::MinSpeed = -1.0f;
const float SiphonLife::DefaultSpeed = 2.0f;
const float SiphonLife::MaxSpeed = 2.5f;
const float SiphonLife::Duration = 6.0f;

SiphonLife* SiphonLife::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	SiphonLife* instance = new SiphonLife(caster, target);

	instance->autorelease();

	return instance;
}

SiphonLife::SiphonLife(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Fangs, BuffData(SiphonLife::Duration, SiphonLife::SiphonLifeIdentifier))
{
	this->clippy = SiphonLifeClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

SiphonLife::~SiphonLife()
{
}

void SiphonLife::onEnter()
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

void SiphonLife::initializePositions()
{
	super::initializePositions();
}

void SiphonLife::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void SiphonLife::registerHackables()
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
				SiphonLife::SiphonLifeIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_SiphonLife::create(),
				HackableAttribute::HackBarColor::Purple,
				UIResources::Menus_Icons_Fangs,
				SiphonLifeGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_RegisterEsi::create()
							->setStringReplacementVariables({ ConstantFloat::create(SiphonLife::MinSpeed, 1), ConstantFloat::create(SiphonLife::MaxSpeed, 1) })
					},
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_RegisterXmm3::create()
							->setStringReplacementVariables(ConstantFloat::create(SiphonLife::DefaultSpeed, 1))
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

	auto hasteFunc = &SiphonLife::applySiphonLife;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void SiphonLife::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
	super::onModifyTimelineSpeed(timelineSpeed, handleCallback);
	
	this->currentSpeed = *timelineSpeed;

	this->applySiphonLife();

	*timelineSpeed = this->currentSpeed;
}

NO_OPTIMIZE void SiphonLife::applySiphonLife()
{
	static volatile float speedBonus;
	static volatile float increment;
	static volatile float* speedBonusPtr;
	static volatile float* incrementPtr;

	speedBonus = 0.0f;
	increment = SiphonLife::DefaultSpeed;
	speedBonusPtr = &speedBonus;
	incrementPtr = &increment;

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

	this->currentSpeed += MathUtils::clamp(speedBonus, SiphonLife::MinSpeed, SiphonLife::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
