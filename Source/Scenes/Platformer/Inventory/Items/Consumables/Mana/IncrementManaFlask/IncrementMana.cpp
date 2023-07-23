#include "IncrementMana.h"

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
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/IncrementManaFlask/IncrementManaFlask.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/IncrementManaFlask/IncrementManaFlaskGenericPreview.h"
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

const std::string IncrementMana::PropertyIncrementManaTutorial = "increment-mana-tutorial";
const std::string IncrementMana::IncrementManaIdentifier = "increment-mana";
const float IncrementMana::TimeBetweenTicks = 0.5f;
const int IncrementMana::HackTicks = 5;
const float IncrementMana::StartDelay = 0.15f;

IncrementMana* IncrementMana::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	IncrementMana* instance = new IncrementMana(caster, target);

	instance->autorelease();

	return instance;
}

IncrementMana::IncrementMana(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ArrowUp, AbilityType::Arcane, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create();
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);
	
	this->healEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

IncrementMana::~IncrementMana()
{
}

void IncrementMana::onEnter()
{
	super::onEnter();

	this->runIncrementMana();

	CombatEvents::TriggerHackableCombatCue();
}

void IncrementMana::initializePositions()
{
	super::initializePositions();
	
	this->healEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 12.0f);
}

void IncrementMana::registerHackables()
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
				IncrementMana::IncrementManaIdentifier,
				Strings::Menus_Hacking_Objects_IncrementManaFlask_IncrementMana_IncrementMana::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_ArrowUp,
				LazyNode<HackablePreview>::create([=](){ return IncrementManaGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Objects_IncrementManaFlask_IncrementMana_RegisterEdi::create(), HackableDataType::Int32
					}
				},
				int(HackFlags::None),
				(float(IncrementMana::HackTicks) * IncrementMana::TimeBetweenTicks) + 0.1f,
				0.0f
			)
		},
	};

	this->hackables = CREATE_HACKABLES(IncrementMana::runRestoreTick, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void IncrementMana::runIncrementMana()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < IncrementManaFlask::HealTicks; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ArrowUp);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				IncrementMana::TimeBetweenTicks * float(healIndex) + IncrementMana::StartDelay, [=]()
			{
				if (!this->healEffect->isPlayingAnimation())
				{
					this->healEffect->playAnimation(FXResources::Heal_Heal_0000, 0.05f);
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

NO_OPTIMIZE void IncrementMana::runRestoreTick()
{
	static volatile int incrementAmount;

	incrementAmount = 0;

	ASM(push ZDI);
	ASM(mov ZDI, 0)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(inc ZDI);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(incrementAmount, edi);

	ASM(pop ZDI);

	incrementAmount = MathUtils::clamp(incrementAmount, -2, 2);

	this->healSound->play();

	CombatEvents::TriggerManaRestore(CombatEvents::ManaRestoreOrDrainArgs(this->caster, this->owner, incrementAmount, this->abilityType));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
