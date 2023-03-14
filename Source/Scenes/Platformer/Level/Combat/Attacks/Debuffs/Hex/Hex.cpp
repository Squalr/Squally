#include "Hex.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Hex/HexGenericPreview.h"
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

#define LOCAL_FUNC_ID_HEX 1

const std::string Hex::HexIdentifier = "hex";

// Note: UI sets precision on these to 1 digit
const float Hex::MinSpeed = -1.25f;
const float Hex::DefaultSpeed = -1.25f;
const float Hex::DefaultHackSpeed = -0.5f; // Keep in sync with the asm
const float Hex::MaxSpeed = 1.0f;
const float Hex::Duration = 10.0f;

// Static to prevent GCC optimization issues
volatile float Hex::currentSpeed = 0.0f;

Hex* Hex::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Hex* instance = new Hex(caster, target);

	instance->autorelease();

	return instance;
}

Hex::Hex(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_VoodooZombie, AbilityType::Shadow, BuffData(Hex::Duration, Hex::HexIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Curse);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura);

	this->spellAura->setColor(Color3B::MAGENTA);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Hex::~Hex()
{
}

void Hex::onEnter()
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

void Hex::initializePositions()
{
	super::initializePositions();
}

void Hex::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HEX,
			HackableCode::HackableCodeInfo(
				Hex::HexIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Hex_Hex::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_VoodooZombie,
				LazyNode<HackablePreview>::create([=](){ return HexGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Debuffs_Hex_RegisterEbx::create()
							->setStringReplacementVariables(ConstantFloat::create(Hex::DefaultSpeed, 2)), true
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Hex_RegisterEsi::create(), true
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Debuffs_Hex_Hex::create(),
						// x86
						std::string("fld dword ptr [esi]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentMul::create()) + 
						std::string("fmul dword ptr [ebx]\n\n") +
						std::string("fstp dword ptr [esi]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Hex_CommentHint::create())
						, // x64
						std::string("fld dword ptr [esi]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentMul::create()) + 
						std::string("fmul dword ptr [ebx]\n\n") +
						std::string("fstp dword ptr [esi]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Hex_CommentHint::create())
					)
				},
				true
			)
		},
	};

	auto func = &Hex::applyHex;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Hex::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
	super::onModifyTimelineSpeed(speed);
	
	this->currentSpeed = *(speed->speed);

	this->applyHex();

	*(speed->speed) = this->currentSpeed;
}

NO_OPTIMIZE void Hex::applyHex()
{
	static volatile float timelineSpeed;
	static volatile float* timelineSpeedPtr;
	static volatile float multiplier;
	static volatile float* multiplierPtr;

	timelineSpeed = this->currentSpeed;
	multiplier = Hex::DefaultSpeed;
	timelineSpeedPtr = &timelineSpeed;
	multiplierPtr = &multiplier;

	ASM_PUSH_EFLAGS();
	ASM(push ZSI);
	ASM(push ZBX);

	ASM_MOV_REG_PTR(ZSI, timelineSpeedPtr);
	ASM_MOV_REG_PTR(ZBX, multiplierPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HEX);
	ASM(fld dword ptr [ZSI]);
	ASM(fmul dword ptr [ZBX]);
	ASM(fstp dword ptr [ZSI]);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZSI);
	ASM_POP_EFLAGS();

	this->currentSpeed = this->currentSpeed + MathUtils::clamp(timelineSpeed, Hex::MinSpeed, Hex::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
