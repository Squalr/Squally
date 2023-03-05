#include "SpellOfBinding.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/SpellOfBinding/SpellOfBindingGenericPreview.h"
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

#define LOCAL_FUNC_ID_RABIES 1

const std::string SpellOfBinding::SpellOfBindingIdentifier = "spell-of-binding";

// Note: UI sets precision on these to 1 digit
const float SpellOfBinding::MinSpeed = -1.25f;
const float SpellOfBinding::DefaultSpeed = -1.25f;
const float SpellOfBinding::DefaultHackSpeed = -0.5f; // Keep in sync with the asm
const float SpellOfBinding::MaxSpeed = 2.0f;
const float SpellOfBinding::Duration = 6.0f;

// Static to prevent GCC optimization issues
volatile float SpellOfBinding::currentSpeed = 0.0f;

SpellOfBinding* SpellOfBinding::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	SpellOfBinding* instance = new SpellOfBinding(caster, target);

	instance->autorelease();

	return instance;
}

SpellOfBinding::SpellOfBinding(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Bite, AbilityType::Shadow, BuffData(SpellOfBinding::Duration, SpellOfBinding::SpellOfBindingIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Curse);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura);

	this->spellAura->setColor(Color3B::MAGENTA);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

SpellOfBinding::~SpellOfBinding()
{
}

void SpellOfBinding::onEnter()
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

void SpellOfBinding::initializePositions()
{
	super::initializePositions();
}

void SpellOfBinding::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RABIES,
			HackableCode::HackableCodeInfo(
				SpellOfBinding::SpellOfBindingIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_SpellOfBinding::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Bite,
				LazyNode<HackablePreview>::create([=](){ return SpellOfBindingGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_RegisterEax::create()
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_RegisterEsi::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentPushSpeed::create()) +
						"fld dword ptr [eax]\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentPushZero::create()) +
						"fldz\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentCompare::create()) +
						"fcompp\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentJump::create()) +
						"jge reduceSpeed\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentElse::create()) +
						"jmp skipCode\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentSpeedDrain::create()) + 
						"reduceSpeed:\n" +
						"mov dword ptr [esi], -0.5f\n\n" +
						"skipCode:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt1::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt2::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt3::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt4::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentPushSpeed::create()) +
						"fld dword ptr [rax]\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentPushZero::create()) +
						"fldz\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentCompare::create()) +
						"fcompp\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentJump::create()) +
						"jge reduceSpeed\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentElse::create()) +
						"jmp skipCode\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SpellOfBinding_CommentSpeedDrain::create()) + 
						"reduceSpeed:\n" +
						"mov dword ptr [rsi], -0.5f\n\n" +
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

	auto func = &SpellOfBinding::applySpellOfBinding;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void SpellOfBinding::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
	super::onModifyTimelineSpeed(speed);
	
	this->currentSpeed = *(speed->speed);

	this->applySpellOfBinding();

	*(speed->speed) = this->currentSpeed;
}

NO_OPTIMIZE void SpellOfBinding::applySpellOfBinding()
{
	static volatile float speedBonus = 0.0f;
	static volatile float* speedBonusPtr;
	static volatile float* currentSpeedPtr;

	speedBonus = 0.0f;
	speedBonusPtr = &speedBonus;
	currentSpeedPtr = &this->currentSpeed;
	
	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZSI);

	ASM_MOV_REG_PTR(ZAX, currentSpeedPtr);
	ASM_MOV_REG_PTR(ZSI, speedBonusPtr);

	// f([i,u])com(p)(p) + fstsw ax + sahf
	// ftst (Compares St(0) to 0.0)
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RABIES);
	ASM(fld dword ptr [ZAX]);
	ASM(fldz);
	ASM(fcompp);
	ASM(jge spellOfBindingReduceSpeed);
	ASM(jmp skipSpellOfBindingCode);
	ASM(spellOfBindingReduceSpeed:);
	ASM(mov dword ptr [ZSI], 0x000000BF); // -0.5f encoded in hex
	ASM(skipSpellOfBindingCode:);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(pop ZSI);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();
	HACKABLES_STOP_SEARCH();

	this->currentSpeed = MathUtils::clamp(this->currentSpeed + speedBonus, SpellOfBinding::MinSpeed, SpellOfBinding::MaxSpeed);
}
END_NO_OPTIMIZE
