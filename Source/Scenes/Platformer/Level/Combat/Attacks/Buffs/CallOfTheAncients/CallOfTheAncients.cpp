#include "CallOfTheAncients.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/CallOfTheAncients/CallOfTheAncientsGenericPreview.h"
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

#define LOCAL_FUNC_ID_COTA 1

const std::string CallOfTheAncients::CallOfTheAncientsIdentifier = "call-of-the-ancients";

const float CallOfTheAncients::Duration = 60.0f;
const int CallOfTheAncients::DamageDealt = 20;

CallOfTheAncients* CallOfTheAncients::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	CallOfTheAncients* instance = new CallOfTheAncients(caster, target);

	instance->autorelease();

	return instance;
}

CallOfTheAncients::CallOfTheAncients(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_RuneGreen, AbilityType::Physical, BuffData(CallOfTheAncients::Duration, CallOfTheAncients::CallOfTheAncientsIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

CallOfTheAncients::~CallOfTheAncients()
{
}

void CallOfTheAncients::onEnter()
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

void CallOfTheAncients::initializePositions()
{
	super::initializePositions();
}

void CallOfTheAncients::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COTA,
			HackableCode::HackableCodeInfo(
				CallOfTheAncients::CallOfTheAncientsIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_CallOfTheAncients_CallOfTheAncients::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_RuneGreen,
				LazyNode<HackablePreview>::create([=](){ return CallOfTheAncientsGenericPreview::create(); }),
				{
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stacks_CommentEquivalentOfMov::create()
							->setStringReplacementVariables({ Strings::Menus_Hacking_RegisterEdx::create(), ConstantString::create(std::to_string(CallOfTheAncients::DamageDealt)) })) + 
						"push 20\n" +
						"pop edx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_CallOfTheAncients_CommentDamageIncrease::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(CallOfTheAncients::DamageDealt)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_CallOfTheAncients_CommentDecreaseInstead::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Common_CommentLexiconStack::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stacks_CommentEquivalentOfMov::create()
							->setStringReplacementVariables({ Strings::Menus_Hacking_RegisterRdx::create(), ConstantString::create(std::to_string(CallOfTheAncients::DamageDealt)) })) + 
						"push 20\n" +
						"pop rdx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_CallOfTheAncients_CommentDamageIncrease::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(CallOfTheAncients::DamageDealt)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_CallOfTheAncients_CommentDecreaseInstead::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Common_CommentLexiconStack::create())
					),
				},
				true
			)
		},
	};

	auto func = &CallOfTheAncients::applyCallOfTheAncients;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void CallOfTheAncients::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyCallOfTheAncients();

	*(int*)(GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer())
		= GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();
}

NO_OPTIMIZE void CallOfTheAncients::applyCallOfTheAncients()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = 0;

	ASM(push ZDX);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COTA);
	ASM(push 20);
	ASM(pop ZDX);
	ASM_NOP16();
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(currentDamageDealtLocal, edx);
	ASM(pop ZDX);

	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
