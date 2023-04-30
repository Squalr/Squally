#include "Focus.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Focus/FocusGenericPreview.h"
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

#define LOCAL_FUNC_ID_FOCUS 1

const std::string Focus::FocusIdentifier = "focus";
const std::string Focus::HackIdentifierFocus = "focus";

const int Focus::MaxMultiplier = 4;
const float Focus::DamageIncrease = 1.0f; // Keep in sync with asm
const float Focus::Duration = 16.0f;

Focus* Focus::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Focus* instance = new Focus(caster, target);

	instance->autorelease();

	return instance;
}

Focus::Focus(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ThrowingStar, AbilityType::Physical, BuffData(Focus::Duration, Focus::FocusIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Focus::~Focus()
{
}

void Focus::onEnter()
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

void Focus::initializePositions()
{
	super::initializePositions();
}

void Focus::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FOCUS,
			HackableCode::HackableCodeInfo(
				Focus::HackIdentifierFocus,
				Strings::Menus_Hacking_Abilities_Buffs_Focus_Focus::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ThrowingStar,
				LazyNode<HackablePreview>::create([=](){ return FocusGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_Focus_RegisterEax::create(), true
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Buffs_Focus_RegisterEsi::create(), true
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
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create(),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentI::create(),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentAdd::create(),
							ConstantString::create("fiadd dword ptr [eax]\n\n"),
							ConstantString::create("fistp dword ptr [esi]\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create(),
							Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create(),
							Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create(),
							ConstantString::create("\n\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Focus_CommentHint::create()
						})
						, // x64
						ConcatString::create({
							ConstantString::create("fild dword ptr [rsi]\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create(),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentI::create(),
							Strings::Menus_Hacking_Abilities_Generic_FPU_CommentAdd::create(),
							ConstantString::create("fiadd dword ptr [rax]\n\n"),
							ConstantString::create("fistp dword ptr [rsi]\n\n"),
							Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create(),
							Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create(),
							Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create(),
							ConstantString::create("\n\n"),
							Strings::Menus_Hacking_Abilities_Buffs_Focus_CommentHint::create()
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Focus::applyFocus, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Focus::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyFocus();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Focus::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Focus::MaxMultiplier);
}

NO_OPTIMIZE void Focus::applyFocus()
{
	static volatile int currentDamageDealtLocal = 0;
	static volatile int* currentDamageDealtLocalPtr = nullptr;
	static volatile int damageIncrease = 0;
	static volatile int* damageIncreasePtr = nullptr;

	currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	damageIncrease = 8;
	damageIncreasePtr = &damageIncrease;
	currentDamageDealtLocal = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZAX, damageIncreasePtr);
	ASM_MOV_REG_VAR(ZSI, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FOCUS);
	ASM(fild dword ptr [ZSI]);
	ASM(fiadd dword ptr [ZAX]);
	ASM(fistp dword ptr [ZSI]);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZSI);
	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
