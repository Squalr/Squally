#include "Fear.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Fear/FearGenericPreview.h"
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

#define LOCAL_FUNC_ID_FEAR 1

const std::string Fear::FearIdentifier = "fear";
const std::string Fear::HackIdentifierFear = "fear";

const int Fear::MaxMultiplier = 4;
const float Fear::Duration = 12.0f;

Fear* Fear::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Fear* instance = new Fear(caster, target);

	instance->autorelease();

	return instance;
}

Fear::Fear(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Skull2, AbilityType::Shadow, BuffData(Fear::Duration, Fear::FearIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

Fear::~Fear()
{
}

void Fear::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void Fear::initializePositions()
{
	super::initializePositions();
}

void Fear::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FEAR,
			HackableCode::HackableCodeInfo(
				Fear::HackIdentifierFear,
				Strings::Menus_Hacking_Abilities_Debuffs_Fear_Fear::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_Skull2,
				LazyNode<HackablePreview>::create([=](){ return FearGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Fear_RegisterEsi::create(), HackableDataType::Int32,
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
							ConstantString::create("shr esi, 2\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Fear_CommentHint::create())
						})
						, // x64
						ConcatString::create({
							ConstantString::create("shr rsi, 2\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Fear_CommentHint::create())
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Fear::applyFear, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Fear::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(damageOrHealing->damageOrHealingValue);

	this->applyFear();

	int min = -std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * Fear::MaxMultiplier);
	int max = std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * Fear::MaxMultiplier);

	*damageOrHealing->damageOrHealing = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	*damageOrHealing->damageOrHealingMin = min;
	*damageOrHealing->damageOrHealingMax = max;
}

NO_OPTIMIZE void Fear::applyFear()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	ASM_PUSH_EFLAGS();
	ASM(push ZSI);

	ASM_MOV_REG_VAR(esi, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FEAR);
	ASM(shr ZSI, 2);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, esi);

	ASM(pop ZSI);
	ASM_POP_EFLAGS();

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
