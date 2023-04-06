#include "Enchantment.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Enchantment/EnchantmentGenericPreview.h"
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

#define LOCAL_FUNC_ID_ENCHANTMENT 1

const std::string Enchantment::EnchantmentIdentifier = "enchantment";
const std::string Enchantment::HackIdentifierEnchantment = "enchantment";

const int Enchantment::MaxMultiplier = 4;
const float Enchantment::Duration = 16.0f;

Enchantment* Enchantment::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Enchantment* instance = new Enchantment(caster, target);

	instance->autorelease();

	return instance;
}

Enchantment::Enchantment(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_WandSkeleton, AbilityType::Physical, BuffData(Enchantment::Duration, Enchantment::EnchantmentIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::MAGENTA);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

Enchantment::~Enchantment()
{
}

void Enchantment::onEnter()
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

void Enchantment::initializePositions()
{
	super::initializePositions();
}

void Enchantment::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_ENCHANTMENT,
			HackableCode::HackableCodeInfo(
				Enchantment::HackIdentifierEnchantment,
				Strings::Menus_Hacking_Abilities_Buffs_Enchantment_Enchantment::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_WandSkeleton,
				LazyNode<HackablePreview>::create([=](){ return EnchantmentGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Buffs_Enchantment_RegisterEdi::create(), true
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Buffs_Enchantment_RegisterEsi::create(), true
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						std::string("fild dword ptr [esi]\n") +
						std::string("fmul dword ptr [edi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentRnd::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentInt::create()) +
						std::string("frndint\n") +
						std::string("fistp dword ptr [esi]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Enchantment_CommentHint::create())
						, // x64
						std::string("fild dword ptr [rsi]\n") +
						std::string("fmul dword ptr [rdi]\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentF::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentRnd::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentInt::create()) +
						std::string("frndint\n") +
						std::string("fistp dword ptr [rsi]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_Enchantment_CommentHint::create())
					),
				},
				true
			)
		},
	};

	auto func = &Enchantment::applyEnchantment;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Enchantment::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyEnchantment();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * Enchantment::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * Enchantment::MaxMultiplier);
}

NO_OPTIMIZE void Enchantment::applyEnchantment()
{
	static volatile int currentDamageDealtLocal = 0;
	static volatile int* currentDamageDealtLocalPtr = nullptr;
	static volatile float damageIncrease = 0.0f;
	static volatile float* damageIncreasePtr = nullptr;

	currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	damageIncrease = 3.0f;
	damageIncreasePtr = &damageIncrease;
	currentDamageDealtLocal = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZDI);
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZDI, damageIncreasePtr);
	ASM_MOV_REG_VAR(ZSI, currentDamageDealtLocalPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_ENCHANTMENT);
	ASM(fild dword ptr [ZSI]);
	ASM(fmul dword ptr [ZDI]);
	ASM(frndint)
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
