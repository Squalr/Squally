#include "Vampirism.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Vampirism/VampirismGenericPreview.h"
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

#define LOCAL_FUNC_ID_VAMPIRISM 1

const std::string Vampirism::VampirismIdentifier = "vampirism";
const std::string Vampirism::HackIdentifierVampirism = "vampirism";

const int Vampirism::MaxMultiplier = 6;
const int Vampirism::DamageDelt = 1;
const float Vampirism::Duration = 24.0f;

Vampirism* Vampirism::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Vampirism* instance = new Vampirism(caster, target);

	instance->autorelease();

	return instance;
}

Vampirism::Vampirism(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_PurpleScarabShell, AbilityType::Nature, BuffData(Vampirism::Duration, Vampirism::VampirismIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

Vampirism::~Vampirism()
{
}

void Vampirism::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void Vampirism::initializePositions()
{
	super::initializePositions();
}

void Vampirism::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_VAMPIRISM,
			HackableCode::HackableCodeInfo(
				Vampirism::HackIdentifierVampirism,
				Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_Vampirism::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_PurpleScarabShell,
				LazyNode<HackablePreview>::create([=](){ return VampirismGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_Register::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_CommentCompare::create()) +
						"cmp edx, 0:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_CommentJump::create()) +
						"jl doNothing\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_CommentConvertToHealing::create()) +
						"mov ecx, edx\n" +
						"imul ecx, -1\n\n" +
						"doNothing:\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_CommentCompare::create()) +
						"cmp rdx, 0:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_CommentJump::create()) +
						"jl doNothing\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Vampirism_CommentConvertToHealing::create()) +
						"mov rcx, rdx\n" +
						"imul rcx, -1\n\n" +
						"doNothing:\n"
					),
				},
				true
			)
		},
	};

	auto func = &Vampirism::applyVampirism;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Vampirism::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(Vampirism::DamageDelt);

	this->applyVampirism();

	int min = -std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * Vampirism::MaxMultiplier);
	int max = std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * Vampirism::MaxMultiplier);

	*damageOrHealing->damageOrHealing = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	*damageOrHealing->damageOrHealingMin = min;
	*damageOrHealing->damageOrHealingMax = max;
}

NO_OPTIMIZE void Vampirism::applyVampirism()
{
	static volatile int currentDamageDealtLocal = 0;
	static volatile int healingLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	// TODO: Another register to store the amount healed on damage

	ASM_PUSH_EFLAGS()
	ASM(push ZDX);
	ASM(push ZCX);

	ASM(MOV ZDX, 0)
	ASM_MOV_REG_VAR(edx, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_VAMPIRISM);
	ASM(cmp ZDX, 0);
	ASM(jl skipCodeVampirism);
	ASM(mov ZCX, ZDX);
	ASM(imul ZCX, -1);
	ASM(skipCodeVampirism:);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(healingLocal, ecx);

	ASM(pop ZCX);
	ASM(pop ZDX);
	ASM_POP_EFLAGS()

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	int max = currentDamageDealtLocal * Vampirism::MaxMultiplier;
	bool overflowedMin = healingLocal >= max;
	bool overflowedMax = healingLocal <= max;
	healingLocal = MathUtils::clamp(healingLocal, -max, max);
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, healingLocal, this->abilityType, true, overflowedMin, overflowedMax));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
