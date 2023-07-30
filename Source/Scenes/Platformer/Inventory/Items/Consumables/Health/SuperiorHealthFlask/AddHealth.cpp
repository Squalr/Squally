#include "AddHealth.h"

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
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/SuperiorHealthFlask/SuperiorHealthFlask.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/SuperiorHealthFlask/AddHealthGenericPreview.h"
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

const std::string AddHealth::PropertyAddHealthTutorial = "increment-health-tutorial";
const std::string AddHealth::AddHealthIdentifier = "increment-health";
const float AddHealth::TimeBetweenTicks = 0.5f;
const int AddHealth::HackTicks = 5;
const float AddHealth::StartDelay = 0.15f;

AddHealth* AddHealth::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	AddHealth* instance = new AddHealth(caster, target);

	instance->autorelease();

	return instance;
}

AddHealth::AddHealth(PlatformerEntity* caster, PlatformerEntity* target)
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

AddHealth::~AddHealth()
{
}

void AddHealth::onEnter()
{
	super::onEnter();

	this->runAddHealth();

	CombatEvents::TriggerHackableCombatCue();
}

void AddHealth::initializePositions()
{
	super::initializePositions();
	
	this->healEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 12.0f);
}

void AddHealth::registerHackables()
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
				AddHealth::AddHealthIdentifier,
				Strings::Menus_Hacking_Objects_SuperiorHealthFlask_AddHealth_AddHealth::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_ArrowUp,
				LazyNode<HackablePreview>::create([=](){ return AddHealthGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Objects_SuperiorHealthFlask_AddHealth_RegisterEdi::create(), HackableDataType::Int32
					}
				},
				int(HackFlags::None),
				(float(AddHealth::HackTicks) * AddHealth::TimeBetweenTicks) + 0.1f,
				0.0f
			)
		},
	};

	this->hackables = CREATE_HACKABLES(AddHealth::runRestoreTick, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void AddHealth::runAddHealth()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < SuperiorHealthFlask::HealTicks; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ArrowUp);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				AddHealth::TimeBetweenTicks * float(healIndex) + AddHealth::StartDelay, [=]()
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

NO_OPTIMIZE void AddHealth::runRestoreTick()
{
	static volatile int addAmount;

	addAmount = 0;

	ASM(push ZDI);
	ASM(mov ZDI, 0)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(add ZDI, 4);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(addAmount, edi);

	ASM(pop ZDI);

	this->healSound->play();

	const int MinHealing = -16;
	const int MaxHealing = 16;

	bool overflowedMin = addAmount < MinHealing;
	bool overflowedMax = addAmount > MaxHealing;

	addAmount = MathUtils::clamp(addAmount, MinHealing, MaxHealing);

	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, addAmount, this->abilityType, false, overflowedMin, overflowedMax));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
