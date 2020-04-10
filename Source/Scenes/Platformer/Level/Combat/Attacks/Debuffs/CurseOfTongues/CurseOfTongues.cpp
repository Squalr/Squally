#include "CurseOfTongues.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CurseOfTongues/CurseOfTonguesClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CurseOfTongues/CurseOfTonguesGenericPreview.h"
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

const std::string CurseOfTongues::CurseOfTonguesIdentifier = "curse-of-tongues";

// Note: UI sets precision on these to 1 digit
const float CurseOfTongues::MinSpeed = -1.25f;
const float CurseOfTongues::DefaultSpeed = -1.25f;
const float CurseOfTongues::DefaultHackSpeed = -0.5f; // Keep in sync with the asm
const float CurseOfTongues::MaxSpeed = 1.0f;
const float CurseOfTongues::Duration = 6.0f;

CurseOfTongues* CurseOfTongues::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	CurseOfTongues* instance = new CurseOfTongues(caster, target);

	instance->autorelease();

	return instance;
}

CurseOfTongues::CurseOfTongues(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Voodoo, BuffData(CurseOfTongues::Duration, CurseOfTongues::CurseOfTonguesIdentifier))
{
	this->clippy = CurseOfTonguesClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Curse);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura);

	this->spellAura->setColor(Color3B::MAGENTA);
	this->spellAura->setOpacity(0);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

CurseOfTongues::~CurseOfTongues()
{
}

void CurseOfTongues::onEnter()
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

void CurseOfTongues::initializePositions()
{
	super::initializePositions();
}

void CurseOfTongues::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void CurseOfTongues::registerHackables()
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
				CurseOfTongues::CurseOfTonguesIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_CurseOfTongues::create(),
				UIResources::Menus_Icons_Voodoo,
				CurseOfTonguesGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_RegisterEsi::create()
							->setStringReplacementVariables({ ConstantFloat::create(CurseOfTongues::MinSpeed, 1), ConstantFloat::create(CurseOfTongues::MaxSpeed, 1) })
					},
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_RegisterXmm3::create()
							->setStringReplacementVariables(ConstantFloat::create(CurseOfTongues::DefaultSpeed, 1))
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				this->clippy,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_ReduceCurse::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_CommentSpeed::create()
							->setStringReplacementVariables(ConstantFloat::create(CurseOfTongues::DefaultHackSpeed, 1))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_CommentGainInstead::create()) + 
						"mov dword ptr [esi], -0.5f\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt4::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()),
						// x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_CommentSpeed::create()
							->setStringReplacementVariables(ConstantFloat::create(CurseOfTongues::DefaultHackSpeed, 1))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_CommentGainInstead::create()) + 
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

	auto hasteFunc = &CurseOfTongues::applyCurseOfTongues;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void CurseOfTongues::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
	super::onModifyTimelineSpeed(timelineSpeed, handleCallback);
	
	this->currentSpeed = *timelineSpeed;

	this->applyCurseOfTongues();

	*timelineSpeed = this->currentSpeed;
}

NO_OPTIMIZE void CurseOfTongues::applyCurseOfTongues()
{
	volatile float speedBonus = 0.0f;
	volatile float increment = CurseOfTongues::DefaultSpeed;
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

	this->currentSpeed += MathUtils::clamp(speedBonus, CurseOfTongues::MinSpeed, CurseOfTongues::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
