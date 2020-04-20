#include "Blind.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Blind/BlindClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Blind/BlindGenericPreview.h"
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

const std::string Blind::BlindIdentifier = "haste";

// Note: UI sets precision on these to 1 digit
const float Blind::MinSpeed = -1.0f;
const float Blind::DefaultSpeed = 2.0f;
const float Blind::MaxSpeed = 2.5f;
const float Blind::Duration = 6.0f;

Blind* Blind::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Blind* instance = new Blind(caster, target);

	instance->autorelease();

	return instance;
}

Blind::Blind(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Eye, BuffData(Blind::Duration, Blind::BlindIdentifier))
{
	this->clippy = BlindClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Blind::~Blind()
{
}

void Blind::onEnter()
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

void Blind::initializePositions()
{
	super::initializePositions();
}

void Blind::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void Blind::registerHackables()
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
				Blind::BlindIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Blind_Blind::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Eye,
				BlindGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Blind_RegisterEsi::create()
							->setStringReplacementVariables({ ConstantFloat::create(Blind::MinSpeed, 1), ConstantFloat::create(Blind::MaxSpeed, 1) })
					},
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Debuffs_Blind_RegisterXmm3::create()
							->setStringReplacementVariables(ConstantFloat::create(Blind::DefaultSpeed, 1))
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Debuffs_Blind_ReduceBlind::create(),
						// x86
						"mov dword ptr [esi], 0.0",
						// x64
						"mov dword ptr [rsi], 0.0"
					)
				}
			)
		},
	};

	auto hasteFunc = &Blind::applyBlind;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void Blind::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
	super::onModifyTimelineSpeed(timelineSpeed, handleCallback);
	
	this->currentSpeed = *timelineSpeed;

	this->applyBlind();

	*timelineSpeed = this->currentSpeed;
}

NO_OPTIMIZE void Blind::applyBlind()
{
	static volatile float speedBonus;
	static volatile float increment;
	static volatile float* speedBonusPtr;
	static volatile float* incrementPtr;

	speedBonus = 0.0f;
	increment = Blind::DefaultSpeed;
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

	this->currentSpeed += MathUtils::clamp(speedBonus, Blind::MinSpeed, Blind::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
