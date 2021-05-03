#include "Regeneration.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Regeneration/RegenerationGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RESTORE 1

const std::string Regeneration::RegenerationIdentifier = "regeneration";
const float Regeneration::TimeBetweenTicks = 1.0f;
const int Regeneration::HealTicks = 3;
const float Regeneration::StartDelay = 0.15f;

Regeneration* Regeneration::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Regeneration* instance = new Regeneration(caster, target);

	instance->autorelease();

	return instance;
}

Regeneration::Regeneration(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_MoonShine, AbilityType::Arcane, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create();
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);
	
	this->healEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

Regeneration::~Regeneration()
{
}

void Regeneration::onEnter()
{
	super::onEnter();

	this->runRegeneration();

	CombatEvents::TriggerHackableCombatCue();
}

void Regeneration::initializePositions()
{
	super::initializePositions();
	
	this->healEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 12.0f);
}

void Regeneration::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RESTORE,
			HackableCode::HackableCodeInfo(
				Regeneration::RegenerationIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Reflect_Reflect::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_MoonShine,
				LazyNode<HackablePreview>::create([=](){ return RegenerationGenericPreview::create(); }),
				{
					// { HackableCode::Register::zdi, Strings::Menus_Hacking_Objects_RegenerationFlask_Regeneration_RegisterEdi::create() }
				},
				int(HackFlags::None),
				(float(Regeneration::HealTicks) * Regeneration::TimeBetweenTicks) + 0.1f,
				0.0f
			)
		},
	};

	auto restoreFunc = &Regeneration::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Regeneration::runRegeneration()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < Regeneration::HealTicks; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ArrowUp);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				Regeneration::TimeBetweenTicks * float(healIndex) + Regeneration::StartDelay, [=]()
			{
				if (!this->healEffect->isPlayingAnimation())
				{
					this->healEffect->playAnimation(FXResources::Restore_Restore_0000, 0.05f);
				}
				
				this->runRestoreTick();
			})
		);
	}

	CombatEvents::TriggerRegisterTimelineEventGroup(CombatEvents::RegisterTimelineEventGroupArgs(
		TimelineEventGroup::create(timelineEvents, this, this->owner, [=]()
		{
			this->removeBuff();
		})
	));
}

NO_OPTIMIZE void Regeneration::runRestoreTick()
{
	static volatile int originalHealth = 0;
	static volatile int health = 0;

	this->owner->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
	{
		originalHealth = healthBehavior->getHealth();
	});

	health = originalHealth;

	ASM(push ZDI);

	ASM_MOV_REG_VAR(edi, health);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(or ZDI, 15);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(health, edi);

	ASM(pop ZDI);

	this->healSound->play();

	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, health - originalHealth, this->abilityType));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
