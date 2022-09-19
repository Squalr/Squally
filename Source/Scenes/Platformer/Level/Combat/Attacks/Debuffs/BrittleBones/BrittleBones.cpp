#include "BrittleBones.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/BrittleBones/BrittleBonesGenericPreview.h"
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

#define LOCAL_FUNC_ID_CURSE_OF_THE_ANCIENTS 1

const std::string BrittleBones::BrittleBonesIdentifier = "brittle-bones";
const std::string BrittleBones::HackIdentifierBrittleBones = "brittle-bones";

const int BrittleBones::MaxMultiplier = 4;
const int BrittleBones::DamageDelt = 1;
const float BrittleBones::Duration = 12.0f;

BrittleBones* BrittleBones::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	BrittleBones* instance = new BrittleBones(caster, target);

	instance->autorelease();

	return instance;
}

BrittleBones::BrittleBones(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_RunePurple, AbilityType::Physical, BuffData(BrittleBones::Duration, BrittleBones::BrittleBonesIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

BrittleBones::~BrittleBones()
{
}

void BrittleBones::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void BrittleBones::initializePositions()
{
	super::initializePositions();
}

void BrittleBones::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_CURSE_OF_THE_ANCIENTS,
			HackableCode::HackableCodeInfo(
				BrittleBones::HackIdentifierBrittleBones,
				Strings::Menus_Hacking_Abilities_Debuffs_BrittleBones_BrittleBones::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_RunePurple,
				LazyNode<HackablePreview>::create([=](){ return BrittleBonesGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_BrittleBones_Register::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stacks_CommentEquivalentOfMov::create()
							->setStringReplacementVariables({ Strings::Menus_Hacking_RegisterEbx::create(), Strings::Menus_Hacking_RegisterEax::create() })) + 
						"push eax\n" +
						"pop ebx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_BrittleBones_CommentDamageSetToValue::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(BrittleBones::DamageDelt)))) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_BrittleBones_CommentIncreaseInstead::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stacks_CommentEquivalentOfMov::create()
							->setStringReplacementVariables({ Strings::Menus_Hacking_RegisterRbx::create(), Strings::Menus_Hacking_RegisterRax::create() })) + 
						"push rax\n" +
						"pop rbx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_BrittleBones_CommentDamageSetToValue::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(BrittleBones::DamageDelt)))) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_BrittleBones_CommentIncreaseInstead::create())
					),
				},
				true
			)
		},
	};

	auto func = &BrittleBones::applyBrittleBones;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void BrittleBones::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(BrittleBones::DamageDelt);

	this->applyBrittleBones();

	// No bounding
	/*
	// Bound multiplier in either direction
	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(MathUtils::clamp(
		Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt(),
		-std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * BrittleBones::MaxMultiplier),
		std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * BrittleBones::MaxMultiplier)
	));*/

	*(int*)(GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer()) = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();
}

NO_OPTIMIZE void BrittleBones::applyBrittleBones()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(eax, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CURSE_OF_THE_ANCIENTS);
	ASM(push ZAX);
	ASM(pop ZBX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, ebx);
	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
