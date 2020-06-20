#include "ArrowRain.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Abilities/ArrowRain/ArrowRainGenericPreview.h"
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

// Static to prevent GCC optimization issues
volatile bool ArrowRain::isOnPlayerTeam = false;

const std::string ArrowRain::HackIdentifierArrowRainTeamCompare = "arrow-rain-team";

ArrowRain* ArrowRain::create(PlatformerEntity* caster, PlatformerEntity* target, std::string arrowResource)
{
	ArrowRain* instance = new ArrowRain(caster, target, arrowResource);

	instance->autorelease();

	return instance;
}

ArrowRain::ArrowRain(PlatformerEntity* caster, PlatformerEntity* target, std::string arrowResource) : super(caster, target, true)
{
	this->arrowPool = std::vector<Sprite*>();
	this->arrowCooldowns = std::vector<float>();
	this->isOnPlayerTeam = false;
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

ArrowRain::~ArrowRain()
{
}

void ArrowRain::onEnter()
{
	super::onEnter();

	this->runArrowRain();
	
	CombatEvents::TriggerHackableCombatCue();
}

void ArrowRain::update(float dt)
{
	super::update(dt);

	this->updateAnimation(dt);
}

Vec2 ArrowRain::getButtonOffset()
{
	return Vec2(0.0f, -768.0f);
}

void ArrowRain::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COMPARE_TEAM,
			HackableCode::HackableCodeInfo(
				ArrowRain::HackIdentifierArrowRainTeamCompare,
				Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_ArrowRain,
				this->createDefaultPreview(),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_RegisterEax::create()
					},
				},
				int(HackFlags::None),
				ArrowRain::StartDelay + ArrowRain::TimeBetweenTicks * float(ArrowRain::TickCount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
						"cmp eax, 1\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentCompare::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CommentEval::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
						"cmp rax, 1\n"
					),
				},
				true
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
	return ArrowRainGenericPreview::create(this->arrowResource);
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

void ArrowRain::updateAnimation(float dt)
{
	float totalDuration = ArrowRain::StartDelay + ArrowRain::TimeBetweenTicks * float(ArrowRain::TickCount);
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
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), std::abs(ArrowRain::Damage), AbilityType::Passive, true));
			}
		}
	}));
}

NO_OPTIMIZE void ArrowRain::compareTeam(TimelineEntry* entry)
{
	static volatile int isOnPlayerTeamLocal;

	isOnPlayerTeamLocal = entry->isPlayerEntry();

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(eax, isOnPlayerTeamLocal);

	ASM(mov ZBX, 1);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM);
	ASM(cmp ZAX, 1);
	ASM_NOP8();
	HACKABLE_CODE_END();

	// If the compare is true, set zax to 1, else 0
	ASM(mov ZAX, 0);
	ASM(cmove ZAX, ZBX);
	ASM_MOV_VAR_REG(isOnPlayerTeamLocal, eax);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	this->isOnPlayerTeam = (isOnPlayerTeamLocal == 0) ? false : true;
}
END_NO_OPTIMIZE
