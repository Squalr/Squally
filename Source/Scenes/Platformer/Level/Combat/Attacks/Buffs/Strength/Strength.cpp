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
#include "Engine/Localization/ConstantString.h"
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

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_STRENGTH 1

const std::string Strength::StrengthIdentifier = "strength";

const int Strength::MinMultiplier = -1; // Keep in sync w/ math clamp
const int Strength::MaxMultiplier = 2;
const int Strength::DamageIncrease = 3; // Keep in sync with asm
const float Strength::Duration = 12.0f;

Strength* Strength::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Strength* instance = new Strength(caster, target);

	instance->autorelease();

	return instance;
}

Strength::Strength(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Strength, BuffData(Strength::Duration, Strength::StrengthIdentifier))
{
	this->clippy = StrengthClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageDelt = 0;
	this->originalDamageDelt = 0;

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Strength::~Strength()
{
}

void Strength::onEnter()
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

void Strength::initializePositions()
{
	super::initializePositions();
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
			LOCAL_FUNC_ID_STRENGTH,
			HackableCode::HackableCodeInfo(
				Strength::StrengthIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Strength_Strength::create(),
				UIResources::Menus_Icons_Strength,
				StrengthGenericPreview::create(),
				{
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Buffs_Strength_RegisterEcx::create()->setStringReplacementVariables(
							{
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(Strength::MinMultiplier))),
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(Strength::MaxMultiplier))),
							})
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				this->clippy,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Strength_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Strength_CommentDamageIncrease::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(Strength::DamageIncrease)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Strength_CommentDecreaseInstead::create()) + 
						"add ecx, 3\n",
						// x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Strength_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Strength_CommentDamageIncrease::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(Strength::DamageIncrease)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Strength_CommentDecreaseInstead::create()) + 
						"add rcx, 3\n"
					),
				},
				true
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

NO_OPTIMIZE void Strength::onBeforeDamageDelt(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
	super::onBeforeDamageDelt(damageOrHealing, handleCallback, caster, target);

	this->originalDamageDelt = *damageOrHealing;

	this->applyStrength();
	
	// Bound multiplier in either direction. Note: Not using static constants due to strange OSX release bug
	this->currentDamageDelt = MathUtils::clamp(this->currentDamageDelt, std::abs(this->originalDamageDelt) * -1, std::abs(this->originalDamageDelt) * 2);
	
	*damageOrHealing = this->currentDamageDelt;
}
END_NO_OPTIMIZE

NO_OPTIMIZE void Strength::applyStrength()
{
	static volatile int damageDelt;

	this->currentDamageDelt = this->originalDamageDelt;
	damageDelt = this->currentDamageDelt;

	ASM(push ZCX);
	ASM_MOV_REG_VAR(ZCX, damageDelt);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_STRENGTH);
	ASM(add ZCX, 3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageDelt, ZCX);

	ASM(pop ZCX);

	this->currentDamageDelt = damageDelt;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
