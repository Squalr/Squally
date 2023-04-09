#include "Daze.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Daze/DazeGenericPreview.h"
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

#define LOCAL_FUNC_ID_DAZE 1

const std::string Daze::DazeIdentifier = "cursed-blade";
const std::string Daze::HackIdentifierDaze = "cursed-blade";

const int Daze::MaxMultiplier = 4;
const float Daze::DazeDamage = 2.0f; // Keep in sync with asm
const float Daze::Duration = 16.0f;

Daze* Daze::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Daze* instance = new Daze(caster, target);

	instance->autorelease();

	return instance;
}

Daze::Daze(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldGlowBlue, AbilityType::Physical, BuffData(Daze::Duration, Daze::DazeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Daze::~Daze()
{
}

void Daze::onEnter()
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

void Daze::initializePositions()
{
	super::initializePositions();
}

void Daze::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_DAZE,
			HackableCode::HackableCodeInfo(
				Daze::HackIdentifierDaze,
				Strings::Menus_Hacking_Abilities_Debuffs_Daze_Daze::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ShieldGlowBlue,
				LazyNode<HackablePreview>::create([=](){ return DazeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_Daze_RegisterEsi::create()
					},
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Debuffs_Daze_RegisterEdi::create()
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(Daze::DazeDamage)))) + 
						std::string("fild dword ptr [esi]\n") +
						std::string("fld dword ptr [edi]\n") +
						std::string("fld dword ptr [eax]\n") +
						std::string("fld dword ptr [ebx]\n") +
						std::string("fcompp\n") +
						std::string("fcmovbe st0, st1\n") +
						std::string("fistp dword ptr [esi]\n") +
						std::string("fstp st(0)\n")
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(Daze::DazeDamage)))) + 
						std::string("fild dword ptr [rsi]\n") +
						std::string("fld dword ptr [rdi]\n") +
						std::string("fld dword ptr [rax]\n") +
						std::string("fld dword ptr [rbx]\n") +
						std::string("fcompp\n") +
						std::string("fcmovbe st0, st1\n") +
						std::string("fistp dword ptr [rsi]\n") +
						std::string("fstp st(0)\n")
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Daze::applyDaze, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Daze::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyDaze();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Daze::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Daze::MaxMultiplier);
}

NO_OPTIMIZE void Daze::applyDaze()
{
	static volatile int currentDamageDealtLocal = 0;
	static volatile int* currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	static volatile float dazeDamage;
	static volatile float* dazeDamagePtr = &dazeDamage;
	static volatile float rng = 0.0f;
	static volatile float chance = 0.0f;
	static volatile float* rngPtr = &rng;
	static volatile float* chancePtr = &chance;

	dazeDamage = Daze::DazeDamage;
	rng = RandomHelper::random_real(0.0f, 1.0f);
	chance = 0.75f;

	currentDamageDealtLocal = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZBX);
	ASM(push ZDI);
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZAX, rngPtr);
	ASM_MOV_REG_VAR(ZBX, chancePtr);
	ASM_MOV_REG_VAR(ZDI, dazeDamagePtr);
	ASM_MOV_REG_VAR(ZSI, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_DAZE);
	ASM(fild dword ptr [ZSI]);
	ASM(fld dword ptr [ZDI]);
	ASM(fld dword ptr [ZAX]);
	ASM(fld dword ptr [ZBX]);
	ASM(fcompp);
	ASM(fcmovbe st(0), st(1));
	ASM(fistp dword ptr [ZSI]);
	ASM(fstp st(0));
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, edi);

	ASM(pop ZSI);
	ASM(pop ZDI);
	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
