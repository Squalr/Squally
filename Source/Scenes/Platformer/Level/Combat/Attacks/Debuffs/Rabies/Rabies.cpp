#include "Rabies.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Rabies/RabiesGenericPreview.h"
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

#define LOCAL_FUNC_ID_RABIES 1

const std::string Rabies::RabiesIdentifier = "rabies";
const std::string Rabies::HackIdentifierRabies = "rabies";

const int Rabies::MaxMultiplier = 6;
const int Rabies::DamageDelt = 1;
const float Rabies::Duration = 24.0f;

Rabies* Rabies::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Rabies* instance = new Rabies(caster, target);

	instance->autorelease();

	return instance;
}

Rabies::Rabies(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_PurpleScarabShell, AbilityType::Nature, BuffData(Rabies::Duration, Rabies::RabiesIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

Rabies::~Rabies()
{
}

void Rabies::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void Rabies::initializePositions()
{
	super::initializePositions();
}

void Rabies::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RABIES,
			HackableCode::HackableCodeInfo(
				Rabies::HackIdentifierRabies,
				Strings::Menus_Hacking_Abilities_Debuffs_Rabies_Rabies::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_PurpleScarabShell,
				LazyNode<HackablePreview>::create([=](){ return RabiesGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_Rabies_Register::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						"cmp edx, 1:\n"
						"jl doNothing\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentDecreaseDamage::create()) +
						"imul edx, -1\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentRepeat::create()) +
						"doNothing:\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentRepeat::create()) +
						"repeat:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentDecreaseDamage::create()) +
						"dec rdx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentCompare::create()) +
						"cmp rdx, 5\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Rabies_CommentRepeatJump::create()) +
						"jg repeat\n"
					),
				},
				true
			)
		},
	};

	auto func = &Rabies::applyRabies;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Rabies::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(Rabies::DamageDelt);

	this->applyRabies();

	int min = -std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * Rabies::MaxMultiplier);
	int max = std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * Rabies::MaxMultiplier);

	*damageOrHealing->damageOrHealing = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	*damageOrHealing->damageOrHealingMin = min;
	*damageOrHealing->damageOrHealingMax = max;
}

NO_OPTIMIZE void Rabies::applyRabies()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZDX);

	ASM(MOV ZDX, 0)
	ASM_MOV_REG_VAR(edx, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RABIES);
	ASM(repeat:);
	ASM(dec ZDX);
	ASM(cmp ZDX, 5);
	ASM(jg repeat);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, edx);

	ASM(pop ZDX);
	ASM_POP_EFLAGS()

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(currentDamageDealtLocal);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
