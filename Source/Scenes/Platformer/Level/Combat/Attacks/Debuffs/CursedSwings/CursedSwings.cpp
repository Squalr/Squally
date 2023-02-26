#include "CursedSwings.h"

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

const std::string CursedSwings::CursedSwingsIdentifier = "cursed-blade";
const std::string CursedSwings::HackIdentifierCursedSwings = "cursed-blade";

const int CursedSwings::MaxMultiplier = 4;
const float CursedSwings::DamageIncrease = 10.0f; // Keep in sync with asm
const float CursedSwings::Duration = 16.0f;

CursedSwings* CursedSwings::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	CursedSwings* instance = new CursedSwings(caster, target);

	instance->autorelease();

	return instance;
}

CursedSwings::CursedSwings(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldGlowBlue, AbilityType::Physical, BuffData(CursedSwings::Duration, CursedSwings::CursedSwingsIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);

	this->spellAura->setColor(Color3B::YELLOW);
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
				UIResources::Menus_Icons_ShieldGlowBlue,
				LazyNode<HackablePreview>::create([=](){ return CursedSwingsGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_RegisterEdi::create()
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_RegisterEsi::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(CursedSwings::DamageIncrease)))) + 
						"fld dword ptr [edi]\n" +
						"fld dword ptr [esi]\n" +
						"fdivp st(1), st(0)\n" +
						"fistp dword ptr [esi]\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedSwings_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(CursedSwings::DamageIncrease)))) + 
						"fld dword ptr [rdi]\n" +
						"fld dword ptr [rsi]\n" +
						"fdivp st(1), st(0)\n" +
						"fistp dword ptr [rsi]\n"
					),
				},
				true
			)
		},
	};

	auto func = &CursedSwings::applyCursedSwings;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

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
	static volatile int* currentDamageDealtLocalPtr = &currentDamageDealtLocal;
	static volatile float damageDivide = 0.0f;
	static volatile float* damageDividePtr = &damageDivide;

	damageDivide = 2.0f;
	currentDamageDealtLocal = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZDI);
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZDI, damageDividePtr);
	ASM_MOV_REG_VAR(ZSI, currentDamageDealtLocalPtr);


	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CURSED_SWINGS);
	ASM(fld dword ptr [ZDI]);
	ASM(fld dword ptr [ZSI]);
	ASM(fdivp st(1), st(0));
	ASM(fistp dword ptr [ZSI]);
	ASM_NOP16();
	HACKABLE_CODE_END();


	ASM_MOV_VAR_REG(currentDamageDealtLocal, edi);

	ASM(pop ZSI);
	ASM(pop ZDI);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
