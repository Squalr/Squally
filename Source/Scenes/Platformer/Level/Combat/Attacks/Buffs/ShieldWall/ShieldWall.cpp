#include "ShieldWall.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ShieldWall/ShieldWallGenericPreview.h"
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

#define LOCAL_FUNC_ID_SHIELD_WALL 1

const std::string ShieldWall::ShieldWallIdentifier = "shield-wall";
const std::string ShieldWall::HackIdentifierShieldWall = "shield-wall";

const int ShieldWall::MaxMultiplier = 4;
const int ShieldWall::DamageReduction = 3; // Keep in sync with asm
const float ShieldWall::Duration = 16.0f;

ShieldWall* ShieldWall::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ShieldWall* instance = new ShieldWall(caster, target);

	instance->autorelease();

	return instance;
}

ShieldWall::ShieldWall(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldGlowOrange, AbilityType::Physical, BuffData(ShieldWall::Duration, ShieldWall::ShieldWallIdentifier))
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

ShieldWall::~ShieldWall()
{
}

void ShieldWall::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
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

void ShieldWall::initializePositions()
{
	super::initializePositions();
}

void ShieldWall::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_SHIELD_WALL,
			HackableCode::HackableCodeInfo(
				ShieldWall::HackIdentifierShieldWall,
				Strings::Menus_Hacking_Abilities_Buffs_ShieldWall_ShieldWall::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ShieldGlowOrange,
				LazyNode<HackablePreview>::create([=](){ return ShieldWallGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_ShieldWall_RegisterEax::create(), true
					},
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Buffs_ShieldWall_RegisterEcx::create(), true
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						std::string("fild dword ptr [ecx]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentI::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentDiv::create()) + 
						std::string("fidiv dword ptr [eax]\n") +
						std::string("fistp dword ptr [ecx]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ShieldWall_CommentHint::create())
						, // x64
						std::string("fild dword ptr [rcx]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentI::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentDiv::create()) + 
						std::string("fidiv dword ptr [rax]\n") +
						std::string("fistp dword ptr [rcx]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ShieldWall_CommentHint::create())
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(ShieldWall::applyShieldWall, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void ShieldWall::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(damageOrHealing->damageOrHealingValue);

	this->applyShieldWall();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * ShieldWall::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * ShieldWall::MaxMultiplier);
}

NO_OPTIMIZE void ShieldWall::applyShieldWall()
{
	static volatile int currentDamageTakenLocal = 0;
	static volatile int* currentDamageTakenLocalPtr = nullptr;
	static volatile int damageReduction = 0;
	static volatile int* damageReductionPtr = nullptr;

	currentDamageTakenLocalPtr = &currentDamageTakenLocal;
	damageReductionPtr = &damageReduction;
	damageReduction = 4;
	currentDamageTakenLocal = Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZCX);

	ASM_MOV_REG_VAR(ZAX, damageReductionPtr);
	ASM_MOV_REG_VAR(ZCX, currentDamageTakenLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SHIELD_WALL);
	ASM(fild dword ptr [ZCX]);
	ASM(fidiv dword ptr [ZAX]);
	ASM(fistp dword ptr [ZCX]);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZCX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(currentDamageTakenLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
