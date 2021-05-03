#include "Regeneration.h"

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
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Abilities/Regeneration/RegenerationGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_COMPARE_TEAM 11

const int Regeneration::TickCount = 6;
const int Regeneration::Damage = 2;
const float Regeneration::TimeBetweenTicks = 0.75f;
const float Regeneration::StartDelay = 0.25f;
const std::string Regeneration::StateKeyIsCasterOnEnemyTeam = "ANTI_OPTIMIZE_STATE_KEY_DAMAGE_TAKEN";

const std::string Regeneration::HackIdentifierRegenerationTeamCompare = "arrow-rain-team";

Regeneration* Regeneration::create(PlatformerEntity* caster, PlatformerEntity* target, std::string arrowResource)
{
	Regeneration* instance = new Regeneration(caster, target, arrowResource);

	instance->autorelease();

	return instance;
}

Regeneration::Regeneration(PlatformerEntity* caster, PlatformerEntity* target, std::string arrowResource) : super(caster, target, true)
{
	this->arrowPool = std::vector<Sprite*>();
	this->arrowCooldowns = std::vector<float>();
	this->arrowResource = arrowResource;

	for (int index = 0; index < 8; index++)
	{
		Sprite* arrow = Sprite::create(arrowResource);

		// Arrows are assumed to point up
		arrow->setRotation(180.0f);
		arrow->setOpacity(0);

		this->arrowPool.push_back(arrow);
		this->arrowCooldowns.push_back(float(index) * 0.4f);

		this->addChild(arrow);
	}
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

void Regeneration::update(float dt)
{
	super::update(dt);

	this->updateAnimation(dt);
}

Vec2 Regeneration::getButtonOffset()
{
	return Vec2(0.0f, -768.0f);
}

void Regeneration::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COMPARE_TEAM,
			HackableCode::HackableCodeInfo(
				Regeneration::HackIdentifierRegenerationTeamCompare,
				Strings::Menus_Hacking_Abilities_Abilities_Regeneration_Regeneration::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_MoonShine,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Abilities_Regeneration_RegisterEdx::create()
					},
				},
				int(HackFlags::None),
				Regeneration::StartDelay + Regeneration::TimeBetweenTicks * float(Regeneration::TickCount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						"cmp eax, 1\n"
						, // x64
						"cmp rax, 1\n"
					),
				},
				true
			)
		},
	};

	auto func = &Regeneration::compareTeam;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* Regeneration::createDefaultPreview()
{
	return RegenerationGenericPreview::create(this->arrowResource);
}

void Regeneration::runRegeneration()
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int index = 0; index < Regeneration::TickCount; index++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_MoonShine);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->caster,
				icon,
				Regeneration::TimeBetweenTicks * float(index) + Regeneration::StartDelay, [=]()
			{
				this->damageOtherTeam();
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

void Regeneration::updateAnimation(float dt)
{
	float totalDuration = Regeneration::StartDelay + Regeneration::TimeBetweenTicks * float(Regeneration::TickCount);
	const float VarianceX = 768.0f;
	const float FallDistance = -1280.0f;
	const float PixelsPerSecond = 768.0f;
	const float Duration = std::abs(FallDistance) / PixelsPerSecond;

	for (int index = 0; index < int(this->arrowCooldowns.size()); index++)
	{
		if (!this->timelinePaused)
		{
			this->arrowCooldowns[index] -= dt;
			this->arrowPool[index]->setPositionY(this->arrowPool[index]->getPositionY() - dt * PixelsPerSecond);
		}

		if (this->arrowCooldowns[index] <= 0.0f)
		{
			this->arrowPool[index]->setOpacity(0);
			this->arrowPool[index]->setPosition(Vec2(RandomHelper::random_real(-VarianceX, VarianceX), 0.0f));
			this->arrowPool[index]->runAction(FadeTo::create(0.25f, 255));

			this->arrowCooldowns[index] = Duration;
		}
	}
}

void Regeneration::damageOtherTeam()
{
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
	{
		TimelineEntry* casterEntry = timeline->getAssociatedEntry(this->caster);
		
		if (casterEntry == nullptr)
		{
			return;
		}

		this->compareTeam(casterEntry);

		for (auto next : timeline->getEntries())
		{
			if (next->isPlayerEntry() == this->HackStateStorage[Regeneration::StateKeyIsCasterOnEnemyTeam].asBool())
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), std::abs(Regeneration::Damage), AbilityType::Passive, true));
			}
		}
	}));
}

NO_OPTIMIZE void Regeneration::compareTeam(TimelineEntry* entry)
{
	static volatile int isOnEnemyTeamLocal;

	isOnEnemyTeamLocal = entry->isPlayerEntry() ? 0 : 1;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM(MOV ZAX, 0);
	ASM_MOV_REG_VAR(eax, isOnEnemyTeamLocal);

	ASM(mov ZBX, 1);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM);
	ASM(cmp ZAX, 1);
	ASM_NOP8();
	HACKABLE_CODE_END();

	// If the compare is true, set zax to 1, else 0
	ASM(MOV ZAX, 0);
	ASM(cmove ZAX, ZBX);

	ASM_MOV_VAR_REG(isOnEnemyTeamLocal, eax);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	this->HackStateStorage[Regeneration::StateKeyIsCasterOnEnemyTeam] = Value((isOnEnemyTeamLocal == 0) ? false : true);
}
END_NO_OPTIMIZE
