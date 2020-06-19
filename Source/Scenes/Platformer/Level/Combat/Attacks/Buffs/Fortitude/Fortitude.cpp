#include "Fortitude.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Fortitude/FortitudeGenericPreview.h"
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

#define LOCAL_FUNC_ID_FORTITUDE 1

const std::string Fortitude::FortitudeIdentifier = "fortitude";
const std::string Fortitude::HackIdentifierFortitude = "fortitude";

const int Fortitude::MaxMultiplier = 4;
const int Fortitude::DamageReduction = 3; // Keep in sync with asm
const float Fortitude::Duration = 16.0f;

Fortitude* Fortitude::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Fortitude* instance = new Fortitude(caster, target);

	instance->autorelease();

	return instance;
}

Fortitude::Fortitude(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldGlowBlue, AbilityType::Physical, BuffData(Fortitude::Duration, Fortitude::FortitudeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->bubble);
	this->addChild(this->spellAura);
}

Fortitude::~Fortitude()
{
}

void Fortitude::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	this->bubble->runAction(FadeTo::create(0.25f, 255));

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void Fortitude::initializePositions()
{
	super::initializePositions();
}

void Fortitude::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FORTITUDE,
			HackableCode::HackableCodeInfo(
				Fortitude::HackIdentifierFortitude,
				Strings::Menus_Hacking_Abilities_Buffs_Fortitude_Fortitude::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ShieldGlowBlue,
				FortitudeGenericPreview::create(),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_Fortitude_RegisterEax::create()->setStringReplacementVariables(
							{
								ConstantString::create(std::to_string(0)),
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(-Fortitude::MaxMultiplier)))
							})
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Fortitude_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Fortitude_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(Fortitude::DamageReduction)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Fortitude_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Fortitude_CommentTryChanging::create()) + 
						"sub ebx, 3\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Fortitude_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Fortitude_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(Fortitude::DamageReduction)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Fortitude_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Fortitude_CommentTryChanging::create()) + 
						"sub rbx, 3\n"
					),
				},
				true
			)
		},
	};

	auto func = &Fortitude::applyFortitude;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Fortitude::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->hackStateStorage[Buff::StateKeyDamageTaken] = Value(damageOrHealing->originalDamageOrHealing);

	this->applyFortitude();

	// Bound multiplier in either direction
	this->hackStateStorage[Buff::StateKeyDamageTaken] = Value(MathUtils::clamp(this->hackStateStorage[Buff::StateKeyDamageTaken].asInt(), -std::abs(damageOrHealing->originalDamageOrHealing * Fortitude::MaxMultiplier), std::abs(damageOrHealing->originalDamageOrHealing * Fortitude::MaxMultiplier)));
	
	(*damageOrHealing->damageOrHealing) = this->hackStateStorage[Buff::StateKeyDamageTaken].asInt();
}

NO_OPTIMIZE void Fortitude::applyFortitude()
{
	static volatile int currentDamageTakenLocal = 0;

	currentDamageTakenLocal = this->hackStateStorage[Buff::StateKeyDamageTaken].asInt();

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZBX, currentDamageTakenLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FORTITUDE);
	ASM(sub ZBX, 3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageTakenLocal, ZBX);

	ASM(pop ZBX);

	this->hackStateStorage[Buff::StateKeyDamageTaken] = Value(currentDamageTakenLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
