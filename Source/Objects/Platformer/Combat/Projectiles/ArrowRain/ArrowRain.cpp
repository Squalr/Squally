#include "ArrowRain.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/ArrowRain/ArrowRainGenericPreview.h"
#include "Objects/Platformer/Combat/Projectiles/ArrowRain/ArrowRainSpeedPreview.h"
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

const int ArrowRain::TickCount = 6;
const int ArrowRain::Damage = 2;
const float ArrowRain::TimeBetweenTicks = 0.75f;
const float ArrowRain::StartDelay = 0.25f;

const std::string ArrowRain::HackIdentifierArrowRainSpeed = "arrow-rain-team";

ArrowRain* ArrowRain::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ArrowRain* instance = new ArrowRain(caster, target);

	instance->autorelease();

	return instance;
}

ArrowRain::ArrowRain(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, true)
{
}

ArrowRain::~ArrowRain()
{
}

void ArrowRain::onEnter()
{
	super::onEnter();

	this->runArrowRain();
}

Vec2 ArrowRain::getButtonOffset()
{
	return Vec2::ZERO;
}

void ArrowRain::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COMPARE_TEAM,
			HackableCode::HackableCodeInfo(
				ArrowRain::HackIdentifierArrowRainSpeed,
				Strings::Menus_Hacking_Objects_Combat_Projectiles_ArrowRain_CompareTeam_CompareTeam::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ArrowRain,
				ArrowRainSpeedPreview::create(),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Combat_Projectiles_ArrowRain_CompareTeam_RegisterEax::create()
					},
				},
				int(HackFlags::None),
				ArrowRain::StartDelay + ArrowRain::TimeBetweenTicks * float(ArrowRain::TickCount),
				0.0f
			)
		},
	};

	auto func = &ArrowRain::compareTeam;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* ArrowRain::createDefaultPreview()
{
	return ArrowRainGenericPreview::create();
}

void ArrowRain::runArrowRain()
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int index = 0; index < ArrowRain::TickCount; index++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ArrowRain);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->caster,
				icon,
				ArrowRain::TimeBetweenTicks * float(index) + ArrowRain::StartDelay, [=]()
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

void ArrowRain::damageOtherTeam()
{
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
	{
		TimelineEntry* casterEntry = timeline->getAssociatedEntry(this->caster);

		bool isCasterPlayerTeam = casterEntry == nullptr ? false : casterEntry->isPlayerEntry();

		for (auto next : timeline->getEntries())
		{
			this->compareTeam(next);

			if (isCasterPlayerTeam != this->isOnPlayerTeam)
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), std::abs(ArrowRain::Damage), AbilityType::Physical, true));
			}
		}
	}));
}

NO_OPTIMIZE void ArrowRain::compareTeam(TimelineEntry* entry)
{
	static volatile int isOnPlayerTeamLocal;

	isOnPlayerTeamLocal = entry->isPlayerEntry();

	ASM(pushfd);
	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZAX, isOnPlayerTeamLocal);

	ASM(mov ZBX, 1);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM);
	ASM(cmp ZAX, 1);
	ASM_NOP8();
	HACKABLE_CODE_END();

	// If the compare is true, set zax to 1, else 0
	ASM(mov ZAX, 0);
	ASM(cmove ZAX, ZBX);
	ASM_MOV_VAR_REG(isOnPlayerTeamLocal, ZAX);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM(popfd);

	HACKABLES_STOP_SEARCH();

	this->isOnPlayerTeam = (isOnPlayerTeamLocal == 0) ? false : true;
}
END_NO_OPTIMIZE
