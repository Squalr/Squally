#include "CursedSwings.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CursedSwings/CursedSwingsGenericPreview.h"
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

#define LOCAL_FUNC_ID_CURSED_SWINGS 1

const std::string CursedSwings::CursedSwingsIdentifier = "cursed-swings";
const std::string CursedSwings::HackIdentifierCursedSwings = "cursed-swings";

const int CursedSwings::MaxMultiplier = 4;
const float CursedSwings::Duration = 16.0f;

CursedSwings* CursedSwings::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	CursedSwings* instance = new CursedSwings(caster, target);

	instance->autorelease();

	return instance;
}

CursedSwings::CursedSwings(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_AxeGlowPurple, AbilityType::Shadow, BuffData(CursedSwings::Duration, CursedSwings::CursedSwingsIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellEffect->setStartColor(Color4F::PURPLE);
	this->spellEffect->setEndColor(Color4F(0.5f, 0.0f, 0.5f, 0.0f));
	this->spellAura->setColor(Color3B::MAGENTA);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

CursedSwings::~CursedSwings()
{
}

void CursedSwings::onEnter()
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

void CursedSwings::initializePositions()
{
	super::initializePositions();
}

void CursedSwings::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_CURSED_SWINGS,
			HackableCode::HackableCodeInfo(
				CursedSwings::HackIdentifierCursedSwings,
				Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CursedSwings::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_AxeGlowPurple,
				LazyNode<HackablePreview>::create([=](){ return CursedSwingsGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_RegisterEdi::create(), true
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_RegisterEsi::create(), true
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
							ConstantString::create("fild dword ptr [esi]\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()), 
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentDiv::create()), 
							ConstantString::create("fdiv dword ptr [edi]\n\n"),
							ConstantString::create("fistp dword ptr [esi]\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()), 
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()),
							ConstantString::create("\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentHint::create())
						})
						, // x64
						ConcatString::create({
							ConstantString::create("fild dword ptr [rsi]\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()), 
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentDiv::create()), 
							ConstantString::create("fdiv dword ptr [rdi]\n\n"),
							ConstantString::create("fistp dword ptr [rsi]\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()), 
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()),
							ConstantString::create("\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentHint::create())
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(CursedSwings::applyCursedSwings, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void CursedSwings::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyCursedSwings();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * CursedSwings::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * CursedSwings::MaxMultiplier);
}

NO_OPTIMIZE void CursedSwings::applyCursedSwings()
{
	static volatile int currentDamageDealtLocal = 0;
	static volatile int* currentDamageDealtLocalPtr = nullptr;
	static volatile float damageDivide = 0.0f;
	static volatile float* damageDividePtr = nullptr;

	currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	damageDividePtr = &damageDivide;
	damageDivide = 2.0f;
	currentDamageDealtLocal = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZDI);
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZDI, damageDividePtr);
	ASM_MOV_REG_VAR(ZSI, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CURSED_SWINGS);
	ASM(fild dword ptr [ZSI]);
	ASM(fdiv dword ptr [ZDI]);
	ASM(fistp dword ptr [ZSI]);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZSI);
	ASM(pop ZDI);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
