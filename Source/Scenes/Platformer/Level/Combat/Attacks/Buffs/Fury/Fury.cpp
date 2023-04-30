#include "Fury.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Fury/FuryGenericPreview.h"
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

#define LOCAL_FUNC_ID_FURY 1

const std::string Fury::FuryIdentifier = "fury";

const int Fury::MinMultiplier = -1;
const int Fury::MaxMultiplier = 2;
const int Fury::DamageIncrease = 3; // Keep in sync with asm
const float Fury::Duration = 12.0f;

// Static to prevent GCC optimization issues
volatile int Fury::currentDamageDealt = 0;

Fury* Fury::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Fury* instance = new Fury(caster, target);

	instance->autorelease();

	return instance;
}

Fury::Fury(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordGlowRed, AbilityType::Physical, BuffData(Fury::Duration, Fury::FuryIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageDealt = 0;

	this->spellAura->setColor(Color3B::GREEN);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Fury::~Fury()
{
}

void Fury::onEnter()
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

void Fury::initializePositions()
{
	super::initializePositions();
}

void Fury::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FURY,
			HackableCode::HackableCodeInfo(
				Fury::FuryIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Fury_Fury::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_SwordGlowRed,
				LazyNode<HackablePreview>::create([=](){ return FuryGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_Fury_RegisterEax::create()
					},
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_Fury_RegisterEax8::create(), true, 8
					},
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_Fury_RegisterEbx::create()
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Buffs_Fury_HintLea::create(),
							ConstantString::create("lea eax, [eax + ebx + 4]\n\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Fury_HintLeaDamage::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zax)),
							ConstantString::create("add dword ptr [eax], 20\n\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Fury_HintDontWorry::create()
						})
						, // x64
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Buffs_Fury_HintLea::create(),
							ConstantString::create("lea rax, [rax + rbx + 4]\n\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Fury_HintLeaDamage::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zax)),
							ConstantString::create("add dword ptr [rax], 20\n\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Fury_HintDontWorry::create()
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Fury::applyFury, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Fury::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->currentDamageDealt = damageOrHealing->damageOrHealingValue;

	this->applyFury();

	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Fury::MinMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Fury::MaxMultiplier);
	(*damageOrHealing->damageOrHealing) = this->currentDamageDealt;
}

NO_OPTIMIZE void Fury::applyFury()
{
	static volatile int currentDamageDealtLocalArr[3];
	static volatile int* currentDamageDealtLocalPtr = nullptr;

	currentDamageDealtLocalArr[0] = 0;
	currentDamageDealtLocalArr[1] = 0;
	currentDamageDealtLocalArr[2] = this->currentDamageDealt;
	currentDamageDealtLocalPtr = currentDamageDealtLocalArr;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_PTR(ZAX, currentDamageDealtLocalPtr);
	ASM(mov ZBX, 4)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FURY);
	ASM(lea ZAX, [ZAX + ZBX + 4]);
	ASM(add dword ptr [ZAX], 40);
	ASM_NOP16();
	HACKABLE_CODE_END();
	
	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	this->currentDamageDealt = currentDamageDealtLocalArr[2];

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
