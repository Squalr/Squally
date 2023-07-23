#include "Diseased.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Diseased/DiseasedGenericPreview.h"
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

#define LOCAL_FUNC_ID_DISEASED 1

const std::string Diseased::DiseasedIdentifier = "diseased";
const std::string Diseased::HackIdentifierDiseased = "diseased";

const int Diseased::MaxMultiplier = 4;
const int Diseased::DamageDelt = 1;
const float Diseased::Duration = 24.0f;

Diseased* Diseased::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Diseased* instance = new Diseased(caster, target);

	instance->autorelease();

	return instance;
}

Diseased::Diseased(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_PurpleScarabShell, AbilityType::Nature, BuffData(Diseased::Duration, Diseased::DiseasedIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

Diseased::~Diseased()
{
}

void Diseased::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void Diseased::initializePositions()
{
	super::initializePositions();
}

void Diseased::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_DISEASED,
			HackableCode::HackableCodeInfo(
				Diseased::HackIdentifierDiseased,
				Strings::Menus_Hacking_Abilities_Debuffs_Diseased_Diseased::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_PurpleScarabShell,
				LazyNode<HackablePreview>::create([=](){ return DiseasedGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_Diseased_Register::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Diseased_CommentRepeat::create()),
							ConstantString::create("repeat:\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Diseased_CommentDecreaseDamage::create()),
							ConstantString::create("dec edx\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Diseased_CommentCompare::create()),
							ConstantString::create("cmp edx, 5\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Diseased_CommentRepeatJump::create()),
							ConstantString::create("jg repeat\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJg::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentG::create())
						})
						, // x64
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Diseased_CommentRepeat::create()),
							ConstantString::create("repeat:\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Diseased_CommentDecreaseDamage::create()),
							ConstantString::create("dec rdx\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Diseased_CommentCompare::create()),
							ConstantString::create("cmp rdx, 5\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Diseased_CommentRepeatJump::create()),
							ConstantString::create("jg repeat\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJg::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentG::create())
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Diseased::applyDiseased, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Diseased::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyDiseased();

	int min = 0;
	int max = std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * Diseased::MaxMultiplier);

	*damageOrHealing->damageOrHealing = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	*damageOrHealing->damageOrHealingMin = min;
	*damageOrHealing->damageOrHealingMax = max;
}

NO_OPTIMIZE void Diseased::applyDiseased()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZDX);

	ASM_MOV_REG_VAR(ZDX, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_DISEASED);
	ASM(repeatDiseased:);
	ASM(dec ZDX);
	ASM(cmp ZDX, 5);
	ASM(jg repeatDiseased);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, edx);

	ASM(pop ZDX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
