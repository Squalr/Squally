#include "Cauterize.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Cauterize/CauterizeGenericPreview.h"
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

const std::string Cauterize::CauterizeIdentifier = "cauterize";
const float Cauterize::TimeBetweenTicks = 1.0f;
const int Cauterize::HealTicks = 5;
const float Cauterize::StartDelay = 0.15f;
const int Cauterize::MaxHealing = 255;

Cauterize* Cauterize::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Cauterize* instance = new Cauterize(caster, target);

	instance->autorelease();

	return instance;
}

Cauterize::Cauterize(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_WandGlowYellow, AbilityType::Nature, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create();
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);
	
	this->healEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

Cauterize::~Cauterize()
{
}

void Cauterize::onEnter()
{
	super::onEnter();

	this->runCauterize();

	CombatEvents::TriggerHackableCombatCue();
}

void Cauterize::initializePositions()
{
	super::initializePositions();
	
	this->healEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 12.0f);
}

void Cauterize::registerHackables()
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
				Cauterize::CauterizeIdentifier,
				Strings::Menus_Hacking_Abilities_Abilities_Cauterize_Cauterize::create(),
				HackableBase::HackBarColor::Green,
				UIResources::Menus_Icons_WandGlowYellow,
				LazyNode<HackablePreview>::create([=](){ return CauterizeGenericPreview::create(); }),
				{
					{ HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Abilities_Cauterize_RegisterEdi::create() }
				},
				int(HackFlags::None),
				(float(Cauterize::HealTicks) * Cauterize::TimeBetweenTicks) + 0.1f,
				0.0f
			)
		},
	};

	auto restoreFunc = &Cauterize::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Cauterize::runCauterize()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < Cauterize::HealTicks; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ArrowUp);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				Cauterize::TimeBetweenTicks * float(healIndex) + Cauterize::StartDelay, [=]()
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

NO_OPTIMIZE void Cauterize::runRestoreTick()
{
	static volatile int originalHealth = 0;
	static volatile int health = 0;

	this->owner->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
	{
		originalHealth = healthBehavior->getHealth();
	});

	health = originalHealth;

	ASM_PUSH_EFLAGS()
	ASM(push ZDI);

	ASM_MOV_REG_VAR(edi, health);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(or ZDI, 15);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(health, edi);

	ASM(pop ZDI);
	ASM_POP_EFLAGS()

	this->healSound->play();

	int delta = MathUtils::clamp(health - originalHealth, -Cauterize::MaxHealing, Cauterize::MaxHealing);
	bool overflowedMin = delta == -Cauterize::MaxHealing;
	bool overflowedMax = delta == Cauterize::MaxHealing;
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, delta, this->abilityType, true, overflowedMin, overflowedMax));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
