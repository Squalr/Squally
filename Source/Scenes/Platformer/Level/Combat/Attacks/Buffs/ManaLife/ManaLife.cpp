#include "ManaLife.h"

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
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ManaLife/ManaLifeGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
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

#define LOCAL_FUNC_ID_MANA_LIFE 1

const std::string ManaLife::ManaLifeIdentifier = "mana-life";
const float ManaLife::Duration = -1.0f;

ManaLife* ManaLife::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ManaLife* instance = new ManaLife(caster, target);

	instance->autorelease();

	return instance;
}

ManaLife::ManaLife(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ShieldMagic, AbilityType::Arcane, BuffData(ManaLife::Duration, ManaLife::ManaLifeIdentifier))
{
}

ManaLife::~ManaLife()
{
}

void ManaLife::onEnter()
{
	super::onEnter();
}

void ManaLife::initializePositions()
{
	super::initializePositions();
}

void ManaLife::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_MANA_LIFE,
			HackableCode::HackableCodeInfo(
				ManaLife::ManaLifeIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_ManaLife_ManaLife::create(),
				HackableBase::HackBarColor::Blue,
				UIResources::Menus_Icons_ShieldMagic,
				LazyNode<HackablePreview>::create([=](){ return ManaLifeGenericPreview::create(); }),
				{
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ManaLife_CommentExplainer::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_ManaLife_CommentExplainer::create())
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(ManaLife::applyManaLife, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

NO_OPTIMIZE
void ManaLife::onAfterDamageTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
	this->applyManaLife();
}
END_NO_OPTIMIZE

NO_OPTIMIZE
void ManaLife::onAfterDamageDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
	this->applyManaLife();
}
END_NO_OPTIMIZE

NO_OPTIMIZE
void ManaLife::onAfterHealingTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
	this->applyManaLife();
}
END_NO_OPTIMIZE

NO_OPTIMIZE
void ManaLife::onAfterHealingDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
	this->applyManaLife();
}
END_NO_OPTIMIZE

NO_OPTIMIZE void ManaLife::applyManaLife()
{
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_MANA_LIFE);
	ASM_NOP16();
	HACKABLE_CODE_END();

	HACKABLES_STOP_SEARCH();

	if (this->owner->getRuntimeStateOrDefaultInt(StateKeys::Mana, 0) <= 0)
	{
		this->owner->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->kill();
		});
	}
}
END_NO_OPTIMIZE
