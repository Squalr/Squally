#include "BlessingOfTheAncients.h"

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
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/BlessingOfTheAncients/BlessingOfTheAncientsGenericPreview.h"
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

#define LOCAL_FUNC_ID_BLESSING 1

const std::string BlessingOfTheAncients::BlessingOfTheAncientsIdentifier = "blessing-of-the-ancients";

const int BlessingOfTheAncients::MinMultiplier = -1;
const int BlessingOfTheAncients::MaxMultiplier = 2;
const int BlessingOfTheAncients::DamageIncrease = 3; // Keep in sync with asm
const float BlessingOfTheAncients::Duration = 12.0f;

// Static to prevent GCC optimization issues
volatile int BlessingOfTheAncients::currentDamageDealt = 0;

BlessingOfTheAncients* BlessingOfTheAncients::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	BlessingOfTheAncients* instance = new BlessingOfTheAncients(caster, target);

	instance->autorelease();

	return instance;
}

BlessingOfTheAncients::BlessingOfTheAncients(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordGlowGreen, AbilityType::Physical, BuffData(BlessingOfTheAncients::Duration, BlessingOfTheAncients::BlessingOfTheAncientsIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageDealt = 0;

	this->spellAura->setColor(Color3B::GREEN);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

BlessingOfTheAncients::~BlessingOfTheAncients()
{
}

void BlessingOfTheAncients::onEnter()
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

void BlessingOfTheAncients::initializePositions()
{
	super::initializePositions();
}

void BlessingOfTheAncients::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_BLESSING,
			HackableCode::HackableCodeInfo(
				BlessingOfTheAncients::BlessingOfTheAncientsIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_BlessingOfTheAncients::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_SwordGlowGreen,
				LazyNode<HackablePreview>::create([=](){ return BlessingOfTheAncientsGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_RegisterEcx4::create()
							->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zcx)), true, 4
					},
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_RegisterEcx8::create()
							->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zcx)), true, 8
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						std::string("push dword ptr [ecx + 4]\n") +
						std::string("pop dword ptr [ecx + 8]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_CommentHint::create()) +
						std::string("\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create())
						, // x64
						std::string("push qword ptr [rcx + 4]\n") +
						std::string("pop qword ptr [rcx + 8]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_CommentHint::create()) +
						std::string("\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create())
					),
				},
				true
			)
		},
	};

	auto func = &BlessingOfTheAncients::applyBlessingOfTheAncients;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void BlessingOfTheAncients::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->currentDamageDealt = damageOrHealing->damageOrHealingValue;

	this->applyBlessingOfTheAncients();

	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * BlessingOfTheAncients::MinMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * BlessingOfTheAncients::MaxMultiplier);
	(*damageOrHealing->damageOrHealing) = this->currentDamageDealt;
}

NO_OPTIMIZE void BlessingOfTheAncients::applyBlessingOfTheAncients()
{
	static volatile int currentDamageDealtLocalArr[3];
	static volatile int* currentDamageDealtLocalPtr = nullptr;

	currentDamageDealtLocalArr[0] = 0;
	currentDamageDealtLocalArr[1] = this->currentDamageDealt * BlessingOfTheAncients::MaxMultiplier;
	currentDamageDealtLocalArr[2] = this->currentDamageDealt;
	currentDamageDealtLocalPtr = currentDamageDealtLocalArr;

	ASM_PUSH_EFLAGS()
	ASM(push ZCX);
	ASM_MOV_REG_PTR(ZCX, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_BLESSING);
	ASM(push ZWORD() ptr [ZCX + 4]);
	ASM(pop ZWORD() ptr [ZCX + 8]);
	ASM_NOP16();
	HACKABLE_CODE_END();
	
	ASM(pop ZCX);
	ASM_POP_EFLAGS()

	this->currentDamageDealt = currentDamageDealtLocalArr[2];

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
