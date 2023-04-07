#include "UnholyProtection.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/UnholyProtection/UnholyProtectionGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNHOLY_PROTECTION 1

const std::string UnholyProtection::UnholyProtectionIdentifier = "unholy-protection";
const std::string UnholyProtection::HackIdentifierUnholyProtection = "unholy-protection";
const float UnholyProtection::Duration = 120.0f;
const std::string UnholyProtection::StateKeyUnholyProtectionNewHealth = "ANTI_OPTIMIZE_STATE_KEY_UNDYING_DAMAGE";

UnholyProtection* UnholyProtection::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	UnholyProtection* instance = new UnholyProtection(caster, target);

	instance->autorelease();

	return instance;
}

UnholyProtection::UnholyProtection(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Tombstone, AbilityType::Shadow, BuffData(UnholyProtection::Duration, UnholyProtection::UnholyProtectionIdentifier))
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

UnholyProtection::~UnholyProtection()
{
}

void UnholyProtection::onEnter()
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

void UnholyProtection::initializePositions()
{
	super::initializePositions();
}

void UnholyProtection::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_UNHOLY_PROTECTION,
			HackableCode::HackableCodeInfo(
				UnholyProtection::HackIdentifierUnholyProtection,
				Strings::Menus_Hacking_Abilities_Buffs_UnholyProtection_UnholyProtection::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Tombstone,
				LazyNode<HackablePreview>::create([=](){ return UnholyProtectionGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Buffs_UnholyProtection_RegisterEax::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_UnholyProtection_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_UnholyProtection_CommentTryChanging::create()) +
						"fld1\n" + // Load one (potential new health) <PUSH>
						"fld dword ptr [eax]\n" +  // Load health <PUSH>
						"fldz\n" + // Load zero <PUSH>
						"fcomp\n" + // Check if health == 0 (death check) <POP>
						"fcmove st(0), st(1)\n" +
						"fistp dword ptr [eax]\n" +
						"fstp st(0)\n" // <POP>
						, // x64 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_UnholyProtection_CommentIncreaseInstead::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_UnholyProtection_CommentTryChanging::create()) + 
						"fld1\n" + // Load one (potential new health) <PUSH>
						"fld dword ptr [rax]\n" +  // Load health <PUSH>
						"fldz\n" + // Load zero <PUSH>
						"fcomp\n" + // Check if health == 0 (death check) <POP>
						"fcmove st(0), st(1)\n" +
						"fistp dword ptr [rax]\n" +
						"fstp st(0)\n" // <POP>
					),
				},
				true
			)
		},
	};

	auto func = &UnholyProtection::applyUnholyProtection;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void UnholyProtection::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	if (damageOrHealing->damageOrHealingValue < 0)
	{
		return;
	}
	
	Buff::HackStateStorage[UnholyProtection::StateKeyUnholyProtectionNewHealth] = Value(1);

	this->applyUnholyProtection();

	(*damageOrHealing->damageOrHealing) =  (damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0) - Buff::HackStateStorage[UnholyProtection::StateKeyUnholyProtectionNewHealth].asInt());
	// *(int*)(GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer()) = Buff::HackStateStorage[UnholyProtection::StateKeyUnholyProtectionNewHealth].asInt();
}

void UnholyProtection::onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeHealingTaken(damageOrHealing);

	if (damageOrHealing->damageOrHealingValue > 0)
	{
		return;
	}

	Buff::HackStateStorage[UnholyProtection::StateKeyUnholyProtectionNewHealth] = Value(1);

	this->applyUnholyProtection();

	(*damageOrHealing->damageOrHealing) =  (damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0) - Buff::HackStateStorage[UnholyProtection::StateKeyUnholyProtectionNewHealth].asInt());
	// *(int*)(GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer()) = Buff::HackStateStorage[UnholyProtection::StateKeyUnholyProtectionNewHealth].asInt();
}

NO_OPTIMIZE void UnholyProtection::applyUnholyProtection()
{
	static volatile int newHealthUnholyProtection = 0;
	static volatile int* newHealthUnholyProtectionPtr = nullptr;
	static volatile int currentDamageTakenLocal = 0;
	static volatile int* currentDamageTakenLocalPtr = nullptr;

	newHealthUnholyProtection = GameUtils::getKeyOrDefault(Buff::HackStateStorage, UnholyProtection::StateKeyUnholyProtectionNewHealth, Value(0)).asInt();
	newHealthUnholyProtection = MathUtils::clamp(newHealthUnholyProtection, 0, std::abs(newHealthUnholyProtection));
	newHealthUnholyProtectionPtr = &newHealthUnholyProtection;
	currentDamageTakenLocal = Buff::HackStateStorage[Buff::StateKeyDamageTaken].asInt();
	currentDamageTakenLocalPtr = &currentDamageTakenLocal;

	ASM_PUSH_EFLAGS()
	ASM(push ZAX);

	ASM_MOV_REG_VAR(ZAX, newHealthUnholyProtection);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_UNHOLY_PROTECTION);
	ASM(fld1); // One (potential new health) <PUSH>
	ASM(fild dword ptr [ZAX]); // Health <PUSH>
	ASM(fldz); // Zero (death check) <PUSH>
	ASM(fcomp); // Check if health == 0 <POP>
	ASM(fcmove st(0), st(1)); // If so, set to 1
	ASM(fistp dword ptr [ZAX]); // <POP>
	ASM(fstp st(0)); // <POP>
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageTakenLocal, edi);

	ASM(pop ZAX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageTaken] = Value(currentDamageTakenLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
