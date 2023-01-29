#include "Manifest.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Manifest/ManifestGenericPreview.h"
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

#define LOCAL_FUNC_ID_MANIFEST 1

const std::string Manifest::ManifestIdentifier = "manifest";

const int Manifest::MinMultiplier = -1;
const int Manifest::MaxMultiplier = 2;
const int Manifest::DamageIncrease = 3; // Keep in sync with asm
const float Manifest::Duration = 12.0f;

// Static to prevent GCC optimization issues
volatile int Manifest::currentDamageDealt = 0;

Manifest* Manifest::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Manifest* instance = new Manifest(caster, target);

	instance->autorelease();

	return instance;
}

Manifest::Manifest(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordGlowRed, AbilityType::Physical, BuffData(Manifest::Duration, Manifest::ManifestIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Curse);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageDealt = 0;

	this->spellAura->setColor(Color3B::GREEN);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Manifest::~Manifest()
{
}

void Manifest::onEnter()
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

void Manifest::initializePositions()
{
	super::initializePositions();
}

void Manifest::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_MANIFEST,
			HackableCode::HackableCodeInfo(
				Manifest::ManifestIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Manifest_Manifest::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_SwordGlowRed,
				LazyNode<HackablePreview>::create([=](){ return ManifestGenericPreview::create(); }),
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
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						// COMMENT("Push speed onto FPU stack")
						"fld dword ptr [eax]\n"
						// COMMENT("Push zero onto FPU stack")
						"fldz\n"
						// COMMENT("Check if speed is > 0, and pop stack twice")
						"fcompp\n"
						// COMMENT("Jump to reduce speed code if speed is > 0")
						"jge reduceSpeed\n"
						// COMMENT("Otherwise, jump over the speed reduction and do nothing")
						"jmp skipCode\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						"reduceSpeed:\n"
						"mov dword ptr [esi], -0.5f\n\n"
						"skipCode:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt4::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						"fld dword ptr [rax]\n"
						"fldz\n"
						"fcompp\n"
						"jge reduceSpeed\n"
						"jmp skipCode\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						"reduceSpeed:\n"
						"mov dword ptr [rsi], -0.5f\n\n"
						"skipCode:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt4::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
					)
				},
				true
			)
		},
	};

	auto func = &Manifest::applyManifest;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Manifest::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->currentDamageDealt = damageOrHealing->damageOrHealingValue;

	this->applyManifest();

	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Manifest::MinMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Manifest::MaxMultiplier);
	(*damageOrHealing->damageOrHealing) = this->currentDamageDealt;
}

NO_OPTIMIZE void Manifest::applyManifest()
{
	static volatile int damageBonus = 0.0f;
	static volatile int* damageBonusPtr;
	static volatile int* currentDamagePtr;

	damageBonus = 0.0f;
	damageBonusPtr = &damageBonus;
	currentDamagePtr = &this->currentDamageDealt;
	
	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZSI);

	ASM_MOV_REG_PTR(ZAX, currentDamagePtr);
	ASM_MOV_REG_PTR(ZSI, damageBonusPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_MANIFEST);
	ASM(fld dword ptr [ZAX]);
	ASM(fldz);
	ASM(fcompp);
	ASM(jge reduceDamage);
	ASM(jmp skipCode);
	ASM(reduceDamage:);
	ASM(mov dword ptr [ZSI], 0x000000BF); // -0.5f encoded in hex
	ASM(skipCode:);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(pop ZSI);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();
	HACKABLES_STOP_SEARCH();

	this->currentDamageDealt = MathUtils::clamp(this->currentDamageDealt + damageBonus, Manifest::MinMultiplier, Manifest::MaxMultiplier);
}
END_NO_OPTIMIZE
