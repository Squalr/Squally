#include "ThickHide.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ThickHide/ThickHideGenericPreview.h"
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

#define LOCAL_FUNC_ID_FORTITUDE 1

const std::string ThickHide::ThickHideIdentifier = "thick-hide";
const std::string ThickHide::HackIdentifierThickHide = "thick-hide";

const int ThickHide::MaxMultiplier = 4;
const int ThickHide::DamageReduction = 3; // Keep in sync with asm
const float ThickHide::Duration = 16.0f;

ThickHide* ThickHide::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ThickHide* instance = new ThickHide(caster, target);

	instance->autorelease();

	return instance;
}

ThickHide::ThickHide(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldGlowBlue, AbilityType::Physical, BuffData(ThickHide::Duration, ThickHide::ThickHideIdentifier))
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

ThickHide::~ThickHide()
{
}

void ThickHide::onEnter()
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

void ThickHide::initializePositions()
{
	super::initializePositions();
}

void ThickHide::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FORTITUDE,
			HackableCode::HackableCodeInfo(
				ThickHide::HackIdentifierThickHide,
				Strings::Menus_Hacking_Abilities_Buffs_ThickHide_ThickHide::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ShieldGlowBlue,
				LazyNode<HackablePreview>::create([=](){ return ThickHideGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_ThickHide_RegisterEbx::create()
					},
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Buffs_ThickHide_RegisterEdx::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ThickHide_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ThickHide_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(ThickHide::DamageReduction)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ThickHide_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ThickHide_CommentTryChanging::create()) + 
						"fisub dword ptr [ebx]\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ThickHide_CommentRegister::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ThickHide_CommentDamageReduce::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(ThickHide::DamageReduction)))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ThickHide_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ThickHide_CommentTryChanging::create()) + 
						"fisub dword ptr [rbx]\n"
					),
				},
				true
			)
		},
	};

	auto func = &ThickHide::applyThickHide;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void ThickHide::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(damageOrHealing->damageOrHealingValue);

	this->applyThickHide();

	(*damageOrHealing->damageOrHealing) = Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();
	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * ThickHide::MaxMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * ThickHide::MaxMultiplier);
}

NO_OPTIMIZE void ThickHide::applyThickHide()
{
	static volatile int currentDamageTakenLocal = 0;
	static volatile int* currentDamageTakenLocalPtr = &currentDamageTakenLocal;
	static volatile int damageReduction = 6;
	static volatile int* damageReductionPtr = &damageReduction;

	currentDamageTakenLocal = Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZBX);
	ASM(push ZDX);

	ASM_MOV_REG_VAR(ZBX, damageReductionPtr);
	ASM_MOV_REG_VAR(ZDX, currentDamageTakenLocalPtr);

	ASM(fild dword ptr [ZDX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FORTITUDE);
	ASM(fisub dword ptr [ZBX]);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(fistp dword ptr [ZDX]);

	ASM_MOV_VAR_REG(currentDamageTakenLocal, ebx);

	ASM(pop ZDX);
	ASM(pop ZBX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(currentDamageTakenLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
