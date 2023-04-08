#include "Rejuvination.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Rejuvination/RejuvinationGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_REJUVINATION 1

const std::string Rejuvination::RejuvinationIdentifier = "rejuvination";
const float Rejuvination::TimeBetweenTicks = 1.0f;
const int Rejuvination::HealTicks = 3;
const int Rejuvination::MaxHealing = 20;
const float Rejuvination::StartDelay = 0.5f;

Rejuvination* Rejuvination::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Rejuvination* instance = new Rejuvination(caster, target);

	instance->autorelease();

	return instance;
}

Rejuvination::Rejuvination(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_MoonShine, AbilityType::Nature, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create();
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);
	
	this->healEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

Rejuvination::~Rejuvination()
{
}

void Rejuvination::onEnter()
{
	super::onEnter();

	this->runRejuvination();

	CombatEvents::TriggerHackableCombatCue();
}

void Rejuvination::initializePositions()
{
	super::initializePositions();
	
	this->healEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 12.0f);
}

void Rejuvination::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_REJUVINATION,
			HackableCode::HackableCodeInfo(
				Rejuvination::RejuvinationIdentifier,
				Strings::Menus_Hacking_Abilities_Abilities_Rejuvination_Rejuvination::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_MoonShine,
				LazyNode<HackablePreview>::create([=](){ return RejuvinationGenericPreview::create(); }),
				{
					{ HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Abilities_Rejuvination_RegisterEdx::create() }
				},
				int(HackFlags::None),
				(float(Rejuvination::HealTicks) * Rejuvination::TimeBetweenTicks) + 0.1f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						"rol edx, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_Rejuvination_Hint::create())
						, // x64
						"rol rdx, 1\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_Rejuvination_Hint::create())
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Rejuvination::runRestoreTick, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Rejuvination::runRejuvination()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < Rejuvination::HealTicks; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ArrowUp);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				Rejuvination::TimeBetweenTicks * float(healIndex) + Rejuvination::StartDelay, [=]()
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

NO_OPTIMIZE void Rejuvination::runRestoreTick()
{
	static volatile int originalHealth = 0;
	static volatile int health = 0;

	this->owner->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
	{
		originalHealth = healthBehavior->getHealth();
	});

	health = originalHealth;

	ASM_PUSH_EFLAGS()
	ASM(push ZDX);

	ASM_MOV_REG_VAR(edx, health);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_REJUVINATION);
	ASM(rol ZDX, 1);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(health, edx);

	ASM(pop ZDX);
	ASM_POP_EFLAGS()

	this->healSound->play();

	int delta = MathUtils::clamp(health - originalHealth, -Rejuvination::MaxHealing, Rejuvination::MaxHealing);
	bool overflowedMin = delta == -Rejuvination::MaxHealing;
	bool overflowedMax = delta == Rejuvination::MaxHealing;
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, delta, this->abilityType, true, overflowedMin, overflowedMax));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
