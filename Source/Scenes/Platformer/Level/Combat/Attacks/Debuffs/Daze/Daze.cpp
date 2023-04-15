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

const std::string Daze::DazeIdentifier = "daze";
const std::string Daze::HackIdentifierDaze = "daze";

const int Daze::MaxMultiplier = 4;
const int Daze::DazeDamage = 2; // Keep in sync with asm
const float Daze::Duration = 16.0f;

Daze* Daze::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Daze* instance = new Daze(caster, target);

	instance->autorelease();

	return instance;
}

Daze::Daze(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Daze, AbilityType::Physical, BuffData(Daze::Duration, Daze::DazeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->dazeFx = SmartAnimationSequenceNode::create();

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->dazeFx);
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
	
	if (!this->dazeFx->isPlayingAnimation())
	{
		this->dazeFx->playAnimationRepeat(FXResources::Dazed_Dazed_000, 0.075f);
	}

	CombatEvents::TriggerHackableCombatCue();
}

void Daze::initializePositions()
{
	super::initializePositions();

	this->dazeFx->setPosition(Vec2(0.0f, 64.0f));
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
				UIResources::Menus_Icons_Daze,
				LazyNode<HackablePreview>::create([=](){ return DazeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_Daze_RegisterEax::create()
					},
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Debuffs_Daze_RegisterEbx::create()
					},
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Debuffs_Daze_RegisterEdi::create()
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Daze_RegisterEsi::create()
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPushChance::create()) +
						std::string("fld dword ptr [esi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPushRng::create()) +
						std::string("fld dword ptr [edi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentCompare::create()) +
						std::string("fcompp\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPushDamageDealt::create()) +
						std::string("fild dword ptr [ebx]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPushDazeDamage::create()) +
						std::string("fild dword ptr [eax]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentF::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentC::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentMov::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentB::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentConditonal::create()) +
						std::string("fcmovbe st0, st1\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPopDamage::create()) +
						std::string("fistp dword ptr [esi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPopStack::create()) +
						std::string("fstp st(0)\n")
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPushChance::create()) +
						std::string("fld dword ptr [rsi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPushRng::create()) +
						std::string("fld dword ptr [rdi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentCompare::create()) +
						std::string("fcompp\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPushDamageDealt::create()) +
						std::string("fild dword ptr [rbx]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPushDazeDamage::create()) +
						std::string("fild dword ptr [rax]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentF::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentC::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentMov::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentB::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentE::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentConditonal::create()) +
						std::string("fcmovbe st0, st1\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPopDamage::create()) +
						std::string("fistp dword ptr [rsi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Daze_CommentPopStack::create()) +
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
	static volatile int dazeDamage;
	static volatile int* dazeDamagePtr = nullptr;
	static volatile float rng = 0.0f;
	static volatile float* rngPtr = nullptr;
	static volatile float chance = 0.0f;
	static volatile float* chancePtr = &chance;

	dazeDamage = Daze::DazeDamage;
	dazeDamagePtr = &dazeDamage;
	rng = RandomHelper::random_real(0.0f, 1.0f);
	rngPtr = &rng;
	chance = 0.75f;
	chancePtr = &chance;

	currentDamageDealtLocal = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZBX);
	ASM(push ZDI);
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZDI, rngPtr);
	ASM_MOV_REG_VAR(ZSI, chancePtr);
	ASM_MOV_REG_VAR(ZAX, dazeDamagePtr);
	ASM_MOV_REG_VAR(ZBX, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_DAZE);
	ASM(fld dword ptr [ZSI]);
	ASM(fld dword ptr [ZDI]);
	ASM(fcompp);
	ASM(fild dword ptr [ZBX]);
	ASM(fild dword ptr [ZAX]);
	ASM(fcmovbe st(0), st(1));
	ASM(fistp dword ptr [ZBX]);
	ASM(fstp st(0));
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZSI);
	ASM(pop ZDI);
	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
