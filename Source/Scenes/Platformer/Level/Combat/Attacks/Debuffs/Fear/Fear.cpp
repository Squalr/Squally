#include "Fear.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantFloat.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Fear/FearGenericPreview.h"
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

const std::string Fear::FearIdentifier = "fear";

// Note: UI sets precision on these to 1 digit
const float Fear::MinSpeed = -1.25f;
const float Fear::DefaultSpeed = -1.25f;
const float Fear::DefaultHackSpeed = -0.5f; // Keep in sync with the asm
const float Fear::MaxSpeed = 1.0f;
const float Fear::Duration = 6.0f;

// Static to prevent GCC optimization issues
volatile float Fear::currentSpeed = 0.0f;

Fear* Fear::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Fear* instance = new Fear(caster, target);

	instance->autorelease();

	return instance;
}

Fear::Fear(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SkullGlowRed, AbilityType::Shadow, BuffData(Fear::Duration, Fear::FearIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Curse);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura);

	this->spellAura->setColor(Color3B::MAGENTA);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Fear::~Fear()
{
}

void Fear::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void Fear::initializePositions()
{
	super::initializePositions();
}

void Fear::registerHackables()
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
				Fear::FearIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Fear_Fear::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_SkullGlowRed,
				LazyNode<HackablePreview>::create([=](){ return FearGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Fear_RegisterEsi::create()
							->setStringReplacementVariables({ ConstantFloat::create(Fear::MinSpeed, 2), ConstantFloat::create(Fear::MaxSpeed, 1) })
					},
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Debuffs_Fear_RegisterXmm3::create()
							->setStringReplacementVariables(ConstantFloat::create(Fear::DefaultSpeed, 2))
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Debuffs_Fear_ReduceCurse::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Fear_CommentSpeed::create()
							->setStringReplacementVariables({ ConstantFloat::create(Fear::DefaultHackSpeed, 1), ConstantFloat::create(Fear::DefaultSpeed, 2) })) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Fear_CommentGainInstead::create()) + 
						"mov dword ptr [esi], -0.5f\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt4::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Fear_CommentSpeed::create()
							->setStringReplacementVariables({ ConstantFloat::create(Fear::DefaultHackSpeed, 1), ConstantFloat::create(Fear::DefaultSpeed, 2) })) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Fear_CommentGainInstead::create()) + 
						"mov dword ptr [rsi], -0.5f\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt4::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
					)
				}
			)
		},
	};

	auto func = &Fear::applyFear;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Fear::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
	super::onModifyTimelineSpeed(speed);
	
	this->currentSpeed = *(speed->speed);

	this->applyFear();

	*(speed->speed) = this->currentSpeed;
}

NO_OPTIMIZE void Fear::applyFear()
{
	static volatile float speedBonus;
	static volatile float increment = 0.0f;
	static volatile float* speedBonusPtr;
	static volatile float* incrementPtr;

	speedBonus = 0.0f;
	increment = Fear::DefaultSpeed;
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

	this->currentSpeed = this->currentSpeed + MathUtils::clamp(speedBonus, Fear::MinSpeed, Fear::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
