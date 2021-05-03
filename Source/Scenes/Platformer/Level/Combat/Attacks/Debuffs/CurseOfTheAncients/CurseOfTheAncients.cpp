#include "CurseOfTheAncients.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CurseOfTheAncients/CurseOfTheAncientsGenericPreview.h"
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

const std::string CurseOfTheAncients::CurseOfTheAncientsIdentifier = "curse-of-the-ancients";
const std::string CurseOfTheAncients::HackIdentifierCurseOfTheAncients = "curse-of-the-ancients";

const int CurseOfTheAncients::MaxMultiplier = 4;
const int CurseOfTheAncients::DamageDelt = 1;
const float CurseOfTheAncients::Duration = 12.0f;

CurseOfTheAncients* CurseOfTheAncients::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	CurseOfTheAncients* instance = new CurseOfTheAncients(caster, target);

	instance->autorelease();

	return instance;
}

CurseOfTheAncients::CurseOfTheAncients(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_RunePurple, AbilityType::Physical, BuffData(CurseOfTheAncients::Duration, CurseOfTheAncients::CurseOfTheAncientsIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

CurseOfTheAncients::~CurseOfTheAncients()
{
}

void CurseOfTheAncients::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void CurseOfTheAncients::initializePositions()
{
	super::initializePositions();
}

void CurseOfTheAncients::registerHackables()
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
				CurseOfTheAncients::HackIdentifierCurseOfTheAncients,
				Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTheAncients_CurseOfTheAncients::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_RunePurple,
				LazyNode<HackablePreview>::create([=](){ return CurseOfTheAncientsGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTheAncients_Register::create(),
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
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTheAncients_CommentDamageSetToValue::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(CurseOfTheAncients::DamageDelt)))) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTheAncients_CommentIncreaseInstead::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stacks_CommentEquivalentOfMov::create()
							->setStringReplacementVariables({ Strings::Menus_Hacking_RegisterRbx::create(), Strings::Menus_Hacking_RegisterRax::create() })) + 
						"push rax\n" +
						"push rbx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTheAncients_CommentDamageSetToValue::create()
							->setStringReplacementVariables(ConstantString::create(std::to_string(CurseOfTheAncients::DamageDelt)))) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTheAncients_CommentIncreaseInstead::create())
					),
				},
				true
			)
		},
	};

	auto func = &CurseOfTheAncients::applyCurseOfTheAncients;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void CurseOfTheAncients::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(CurseOfTheAncients::DamageDelt);

	this->applyCurseOfTheAncients();

	// No bounding
	/*
	// Bound multiplier in either direction
	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(MathUtils::clamp(
		this->HackStateStorage[Buff::StateKeyDamageDealt].asInt(),
		-std::abs(this->HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * CurseOfTheAncients::MaxMultiplier),
		std::abs(this->HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * CurseOfTheAncients::MaxMultiplier)
	));*/

	*(int*)(GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageOrHealingPtr, Value(nullptr)).asPointer()) = GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();
}

NO_OPTIMIZE void CurseOfTheAncients::applyCurseOfTheAncients()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(this->HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

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

	this->HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
