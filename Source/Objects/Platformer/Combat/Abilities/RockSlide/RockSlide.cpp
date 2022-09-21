#include "RockSlide.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Abilities/RockSlide/RockSlideGenericPreview.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_ROCK_SLIDE 11

const int RockSlide::TickCount = 3;
const int RockSlide::MaxDamage = 20;
const float RockSlide::TimeBetweenTicks = 1.5f;
const float RockSlide::StartDelay = 0.25f;
const std::string RockSlide::StateKeyIsCasterOnEnemyTeam = "ANTI_OPTIMIZE_STATE_KEY_DAMAGE_TAKEN";

const std::string RockSlide::HackIdentifierRockSlideTeamCompare = "rock-slide-team";

RockSlide* RockSlide::create(PlatformerEntity* caster, PlatformerEntity* target, std::string rockResource)
{
	RockSlide* instance = new RockSlide(caster, target, rockResource);

	instance->autorelease();

	return instance;
}

RockSlide::RockSlide(PlatformerEntity* caster, PlatformerEntity* target, std::string rockResource) : super(caster, target, true)
{
	this->rockResource = rockResource;

	for (int index = 0; index < 8; index++)
	{
		Sprite* rock = Sprite::create(rockResource);

		// Arrows are assumed to point up
		rock->setRotation(180.0f);
		rock->setOpacity(0);

		this->rockPool.push_back(rock);
		this->rockCooldowns.push_back(float(index) * 0.4f);

		this->addChild(rock);
	}
}

RockSlide::~RockSlide()
{
}

void RockSlide::onEnter()
{
	super::onEnter();

	this->runRockSlide();
	
	CombatEvents::TriggerHackableCombatCue();
}

void RockSlide::update(float dt)
{
	super::update(dt);

	this->updateAnimation(dt);
}

Vec2 RockSlide::getButtonOffset()
{
	return Vec2(0.0f, -768.0f);
}

void RockSlide::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_ROCK_SLIDE,
			HackableCode::HackableCodeInfo(
				RockSlide::HackIdentifierRockSlideTeamCompare,
				Strings::Menus_Hacking_Abilities_Abilities_RockSlide_RockSlide::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_RocksDark,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Abilities_RockSlide_RegisterEdi::create()
					},
				},
				int(HackFlags::None),
				RockSlide::StartDelay + RockSlide::TimeBetweenTicks * float(RockSlide::TickCount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						"ror edi, 1\n"
						, // x64
						"ror rdi, 1\n"
					),
				},
				true
			)
		},
	};

	auto func = &RockSlide::damagePlayerEntity;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* RockSlide::createDefaultPreview()
{
	return RockSlideGenericPreview::create(this->rockResource);
}

void RockSlide::runRockSlide()
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int index = 0; index < RockSlide::TickCount; index++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_RocksDark);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->caster,
				icon,
				RockSlide::TimeBetweenTicks * float(index) + RockSlide::StartDelay, [=]()
			{
				this->damageEntities();
			})
		);
	}

	CombatEvents::TriggerRegisterTimelineEventGroup(CombatEvents::RegisterTimelineEventGroupArgs(
		TimelineEventGroup::create(timelineEvents, nullptr, this->caster, [=]()
		{
			this->despawn();
		})
	));
}

void RockSlide::updateAnimation(float dt)
{
	static const float VarianceX = 768.0f;
	static const float FallDistance = -1280.0f;
	static const float PixelsPerSecond = 768.0f;
	static const float Duration = std::abs(FallDistance) / PixelsPerSecond;

	float totalDuration = RockSlide::StartDelay + RockSlide::TimeBetweenTicks * float(RockSlide::TickCount);

	for (int index = 0; index < int(this->rockCooldowns.size()); index++)
	{
		if (!this->timelinePaused)
		{
			this->rockCooldowns[index] -= dt;
			this->rockPool[index]->setPositionY(this->rockPool[index]->getPositionY() - dt * PixelsPerSecond);
		}

		if (this->rockCooldowns[index] <= 0.0f)
		{
			this->rockPool[index]->setOpacity(0);
			this->rockPool[index]->setPosition(Vec2(RandomHelper::random_real(-VarianceX, VarianceX), 0.0f));
			this->rockPool[index]->runAction(FadeTo::create(0.25f, 255));

			this->rockCooldowns[index] = Duration;
		}
	}
}

void RockSlide::damageEntities()
{
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
	{
		TimelineEntry* casterEntry = timeline->getAssociatedEntry(this->caster);
		
		if (casterEntry == nullptr)
		{
			return;
		}

		for (TimelineEntry* next : timeline->getEntries())
		{
			this->damagePlayerEntity(next->getEntity());
		}
	}));
}

NO_OPTIMIZE void RockSlide::damagePlayerEntity(PlatformerEntity* entity)
{
	static volatile int originalHealth = 0;
	static volatile int health = 0;
	
	if (entity != nullptr)
	{
		entity->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
		{
			originalHealth = healthBehavior->getHealth();
		});
	}

	health = originalHealth;

	ASM(push ZDI);

	ASM_MOV_REG_VAR(edi, health);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_ROCK_SLIDE);
	ASM(ror ZDI, 1);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(health, edi);

	ASM(pop ZDI);

	int delta = MathUtils::clamp(originalHealth - health, -RockSlide::MaxDamage, RockSlide::MaxDamage);
	bool overflowedMin = delta == -RockSlide::MaxDamage;
	bool overflowedMax = delta == RockSlide::MaxDamage;
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, entity, delta, AbilityType::Nature, true, overflowedMin, overflowedMax));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
