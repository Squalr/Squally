#include "Haste.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Haste/HasteGenericPreview.h"
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

const std::string Haste::HasteIdentifier = "haste";

// Note: UI sets precision on these to 1 digit unless otherwise specified
const float Haste::MinSpeed = -0.75f;
const float Haste::DefaultSpeed = 2.0f;
const float Haste::MaxSpeed = 2.5f;
const float Haste::Duration = 6.0f;

// Static to prevent GCC optimization issues
volatile float Haste::currentSpeed = 0.0f;

Haste* Haste::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Haste* instance = new Haste(caster, target);

	instance->autorelease();

	return instance;
}

Haste::Haste(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_HourGlass, AbilityType::Physical, BuffData(Haste::Duration, Haste::HasteIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Haste::~Haste()
{
}

void Haste::onEnter()
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

void Haste::initializePositions()
{
	super::initializePositions();
}

void Haste::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HASTE,
			HackableCode::HackableCodeInfo(
				Haste::HasteIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Haste_Haste::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_HourGlass,
				HasteGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Buffs_Haste_RegisterEsi::create()
							->setStringReplacementVariables({ ConstantFloat::create(Haste::MinSpeed, 2), ConstantFloat::create(Haste::MaxSpeed, 1) })
					},
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Buffs_Haste_RegisterXmm3::create()
							->setStringReplacementVariables(ConstantFloat::create(Haste::DefaultSpeed, 1))
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Buffs_Haste_ReduceHaste::create(),
						// x86
						"mov dword ptr [esi], 0.0f"
						, // x64
						"mov dword ptr [rsi], 0.0f"
					)
				}
			)
		},
	};

	auto func = &Haste::applyHaste;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Haste::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
	super::onModifyTimelineSpeed(speed);

	this->currentSpeed = *(speed->speed);

	this->applyHaste();

	*(speed->speed) = this->currentSpeed;
}

NO_OPTIMIZE void Haste::applyHaste()
{
	static volatile float speedBonus;
	static volatile float increment;
	static volatile float* speedBonusPtr;
	static volatile float* incrementPtr;

	speedBonus = 0.0f;
	increment = Haste::DefaultSpeed;
	speedBonusPtr = &speedBonus;
	incrementPtr = &increment;

	ASM(push ZSI);
	ASM(push ZBX);
	ASM_MOV_REG_PTR(ZSI, speedBonusPtr);
	ASM_MOV_REG_PTR(ZBX, incrementPtr);
	ASM(movss xmm3, [ZBX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(movss [ZSI], xmm3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZSI);

	this->currentSpeed += MathUtils::clamp(speedBonus, Haste::MinSpeed, Haste::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
