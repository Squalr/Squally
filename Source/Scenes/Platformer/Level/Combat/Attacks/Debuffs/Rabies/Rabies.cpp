#include "Rabies.h"

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
#include "Engine/Localization/ConstantFloat.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Rabies/RabiesGenericPreview.h"
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

const std::string Rabies::RabiesIdentifier = "rabies";

// Note: UI sets precision on these to 1 digit
const float Rabies::MinSpeed = -1.25f;
const float Rabies::DefaultSpeed = -1.25f;
const float Rabies::DefaultHackSpeed = -0.5f; // Keep in sync with the asm
const float Rabies::MaxSpeed = 2.0f;
const float Rabies::Duration = 6.0f;

// Static to prevent GCC optimization issues
volatile float Rabies::currentSpeed = 0.0f;

Rabies* Rabies::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Rabies* instance = new Rabies(caster, target);

	instance->autorelease();

	return instance;
}

Rabies::Rabies(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Bite, AbilityType::Shadow, BuffData(Rabies::Duration, Rabies::RabiesIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Curse);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Rabies::~Rabies()
{
}

void Rabies::onEnter()
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

void Rabies::initializePositions()
{
	super::initializePositions();
}

void Rabies::registerHackables()
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
				Rabies::RabiesIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Rabies_Rabies::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Bite,
				LazyNode<HackablePreview>::create([=](){ return RabiesGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_Rabies_RegisterEax::create()
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Rabies_RegisterEcx::create()
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Rabies_RegisterEsi::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create(),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentPushSpeed::create(),
							ConstantString::create("fld dword ptr [ecx]\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentPushZero::create(),
							ConstantString::create("fldz\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentCompare::create(),
							ConstantString::create("fcompp\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CompEFlags::create(),
							ConstantString::create("fstsw ax\n"),
							ConstantString::create("sahf\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentJump::create(),
							ConstantString::create("jge reduceSpeed\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentElse::create(),
							ConstantString::create("jmp skipCode\n\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentSpeedDrain::create(),
							ConstantString::create("reduceSpeed:\n"),
							ConstantString::create("mov dword ptr [esi], -0.5f\n\n"),
							ConstantString::create("skipCode:\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJge::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentGe::create(),
							ConstantString::create("\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt1::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt2::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt3::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt4::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()
						})
						, // x64
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create(),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentPushSpeed::create(),
							ConstantString::create("fld dword ptr [rcx]\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentPushZero::create(),
							ConstantString::create("fldz\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentCompare::create(),
							ConstantString::create("fcompp\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CompEFlags::create(),
							ConstantString::create("fstsw ax\n"),
							ConstantString::create("sahf\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentJump::create(),
							ConstantString::create("jge reduceSpeed\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentElse::create(),
							ConstantString::create("jmp skipCode\n\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentSpeedDrain::create(),
							ConstantString::create("reduceSpeed:\n"),
							ConstantString::create("mov dword ptr [rsi], -0.5f\n\n"),
							ConstantString::create("skipCode:\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJge::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create(),
							Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentGe::create(),
							ConstantString::create("\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt1::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt2::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt3::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentFloatPt4::create(),
							Strings::Menus_Hacking_Abilities_Generic_CommentBreak::create()
						})
					)
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Rabies::applyRabies, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Rabies::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
	super::onModifyTimelineSpeed(speed);
	
	this->currentSpeed = *(speed->speed);

	this->applyRabies();

	*(speed->speed) = this->currentSpeed;
}

NO_OPTIMIZE void Rabies::applyRabies()
{
	static volatile float speedBonus = 0.0f;
	static volatile float* speedBonusPtr;
	static volatile float* currentSpeedPtr;

	speedBonus = -0.5f;
	speedBonusPtr = &speedBonus;
	currentSpeedPtr = &this->currentSpeed;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZCX);
	ASM(push ZSI);

	ASM(mov ZAX, 0)
	ASM_MOV_REG_PTR(ZCX, currentSpeedPtr);
	ASM_MOV_REG_PTR(ZSI, speedBonusPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RABIES);
	ASM(fld dword ptr [ZCX]);
	ASM(fldz);
	ASM(fcompp);
	ASM(fstsw ax);	// Store in AX
	ASM(sahf);		// Convert to eflags
	ASM(jge rabiesReduceSpeed);
	ASM(jmp skipRabiesCode);
	ASM(rabiesReduceSpeed:);
	ASM(mov dword ptr [ZSI], 0xBF000000); // -0.5f encoded in hex
	ASM(skipRabiesCode:);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZSI);
	ASM(pop ZCX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();
	HACKABLES_STOP_SEARCH();

	this->currentSpeed = MathUtils::clamp(this->currentSpeed + speedBonus, Rabies::MinSpeed, Rabies::MaxSpeed);
}
END_NO_OPTIMIZE
