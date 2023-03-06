#include "CursedBlade.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CursedBlade/CursedBladeGenericPreview.h"
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

#define LOCAL_FUNC_ID_CURSED_BLADE 1

const std::string CursedBlade::CursedBladeIdentifier = "cursed-blade";
const std::string CursedBlade::HackIdentifierCursedBlade = "cursed-blade";

const int CursedBlade::MaxMultiplier = 6;
const int CursedBlade::DamageDelt = 1;
const float CursedBlade::Duration = 24.0f;

CursedBlade* CursedBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	CursedBlade* instance = new CursedBlade(caster, target);

	instance->autorelease();

	return instance;
}

CursedBlade::CursedBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_PurpleScarabShell, AbilityType::Nature, BuffData(CursedBlade::Duration, CursedBlade::CursedBladeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);

	this->addChild(this->spellEffect);
}

CursedBlade::~CursedBlade()
{
}

void CursedBlade::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void CursedBlade::initializePositions()
{
	super::initializePositions();
}

void CursedBlade::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_CURSED_BLADE,
			HackableCode::HackableCodeInfo(
				CursedBlade::HackIdentifierCursedBlade,
				Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CursedBlade::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_PurpleScarabShell,
				LazyNode<HackablePreview>::create([=](){ return CursedBladeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_Register::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentRepeat::create()) +
						"repeat:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentDecreaseDamage::create()) +
						"dec edx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentCompare::create()) +
						"cmp edx, 5\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentRepeatJump::create()) +
						"jg repeat\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentRepeat::create()) +
						"repeat:\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentDecreaseDamage::create()) +
						"dec rdx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentCompare::create()) +
						"cmp rdx, 5\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_CursedBlade_CommentRepeatJump::create()) +
						"jg repeat\n"
					),
				},
				true
			)
		},
	};

	auto func = &CursedBlade::applyCursedBlade;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void CursedBlade::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	Buff::HackStateStorage[Buff::StateKeyDamageDealt] = Value(CursedBlade::DamageDelt);

	this->applyCursedBlade();

	int min = -std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * CursedBlade::MaxMultiplier);
	int max = std::abs(Buff::HackStateStorage[Buff::StateKeyOriginalDamageOrHealing].asInt() * CursedBlade::MaxMultiplier);

	*damageOrHealing->damageOrHealing = Buff::HackStateStorage[Buff::StateKeyDamageDealt].asInt();
	*damageOrHealing->damageOrHealingMin = min;
	*damageOrHealing->damageOrHealingMax = max;
}

NO_OPTIMIZE void CursedBlade::applyCursedBlade()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = GameUtils::getKeyOrDefault(Buff::HackStateStorage, Buff::StateKeyDamageDealt, Value(0)).asInt();

	ASM_PUSH_EFLAGS()
	ASM(push ZDX);

	ASM(MOV ZDX, 0)
	ASM_MOV_REG_VAR(edx, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CURSED_BLADE);
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
