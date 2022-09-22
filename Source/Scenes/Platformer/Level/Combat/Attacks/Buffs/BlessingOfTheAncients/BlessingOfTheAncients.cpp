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

#define LOCAL_FUNC_ID_STRENGTH 1

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
	: super(caster, target, UIResources::Menus_Icons_Gauntlet, AbilityType::Physical, BuffData(BlessingOfTheAncients::Duration, BlessingOfTheAncients::BlessingOfTheAncientsIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageDealt = 0;

	this->spellAura->setColor(Color3B::YELLOW);
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
		/*
		{
			LOCAL_FUNC_ID_STRENGTH,
			HackableCode::HackableCodeInfo(
				BlessingOfTheAncients::BlessingOfTheAncientsIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_BlessingOfTheAncients::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_Gauntlet,
				LazyNode<HackablePreview>::create([=](){ return BlessingOfTheAncientsGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_RegisterEcx::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_CommentDamageIncrease::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(BlessingOfTheAncients::DamageIncrease)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_CommentDecreaseInstead::create()) + 
						"add ecx, 3\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_CommentDamageIncrease::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(BlessingOfTheAncients::DamageIncrease)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_BlessingOfTheAncients_CommentDecreaseInstead::create()) + 
						"add rcx, 3\n"
					),
				},
				true
			)
		},
		*/
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
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = this->currentDamageDealt;

	ASM_PUSH_EFLAGS()
	ASM(push ZCX);
	ASM_MOV_REG_VAR(ecx, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_STRENGTH);
	ASM(add ZCX, 3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, ecx);

	ASM(pop ZCX);
	ASM_POP_EFLAGS()

	this->currentDamageDealt = currentDamageDealtLocal;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
