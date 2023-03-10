#include "ArrowVolley.h"

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
#include "Objects/Platformer/Combat/Abilities/ArrowVolley/ArrowVolleyGenericPreview.h"
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

#define LOCAL_FUNC_ID_COMPARE_TEAM 11

const int ArrowVolley::TickCount = 6;
const int ArrowVolley::Damage = 4;
const float ArrowVolley::TimeBetweenTicks = 0.75f;
const float ArrowVolley::StartDelay = 0.25f;
const std::string ArrowVolley::StateKeyIsCasterOnEnemyTeam = "ANTI_OPTIMIZE_STATE_KEY_DAMAGE_TAKEN";

const std::string ArrowVolley::HackIdentifierArrowVolleyTeamCompare = "arrow-volley-team";

ArrowVolley* ArrowVolley::create(PlatformerEntity* caster, PlatformerEntity* target, std::string arrowResource)
{
	ArrowVolley* instance = new ArrowVolley(caster, target, arrowResource);

	instance->autorelease();

	return instance;
}

ArrowVolley::ArrowVolley(PlatformerEntity* caster, PlatformerEntity* target, std::string arrowResource) : super(caster, target, true)
{
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

ArrowVolley::~ArrowVolley()
{
}

void ArrowVolley::onEnter()
{
	super::onEnter();

	this->runArrowVolley();
	
	CombatEvents::TriggerHackableCombatCue();
}

void ArrowVolley::update(float dt)
{
	super::update(dt);

	this->updateAnimation(dt);
}

Vec2 ArrowVolley::getButtonOffset()
{
	return Vec2(0.0f, -768.0f);
}

void ArrowVolley::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COMPARE_TEAM,
			HackableCode::HackableCodeInfo(
				ArrowVolley::HackIdentifierArrowVolleyTeamCompare,
				Strings::Menus_Hacking_Abilities_Abilities_ArrowVolley_CompareTeam::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Crossbow,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Abilities_ArrowVolley_RegisterEax::create()
					},
				},
				int(HackFlags::None),
				ArrowVolley::StartDelay + ArrowVolley::TimeBetweenTicks * float(ArrowVolley::TickCount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowVolley_CommentCompare::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowVolley_CommentEval::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())) +
						"test eax, eax\n" +
						"jns skipAssign\n" +
						"mov ebx, 1\n" +
						"skipAssign\n"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowVolley_CommentCompare::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_ArrowVolley_CommentEval::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())) + 
						"test rax, rax\n" +
						"jns skipAssign\n" +
						"mov rbx, 1\n" +
						"skipAssign\n"
					),
				},
				true
			)
		},
	};

	auto func = &ArrowVolley::compareTeam;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* ArrowVolley::createDefaultPreview()
{
	return ArrowVolleyGenericPreview::create(this->arrowResource);
}

void ArrowVolley::runArrowVolley()
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int index = 0; index < ArrowVolley::TickCount; index++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_Crossbow);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->caster,
				icon,
				ArrowVolley::TimeBetweenTicks * float(index) + ArrowVolley::StartDelay, [=]()
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

void ArrowVolley::updateAnimation(float dt)
{
	static const float VarianceX = 768.0f;
	static const float FallDistance = -1280.0f;
	static const float PixelsPerSecond = 768.0f;
	static const float Duration = std::abs(FallDistance) / PixelsPerSecond;

	float totalDuration = ArrowVolley::StartDelay + ArrowVolley::TimeBetweenTicks * float(ArrowVolley::TickCount);

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

void ArrowVolley::damageOtherTeam()
{
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
	{
		TimelineEntry* casterEntry = timeline->getAssociatedEntry(this->caster);
		
		if (casterEntry == nullptr)
		{
			return;
		}

		this->compareTeam(casterEntry);

		for (TimelineEntry* next : timeline->getEntries())
		{
			if (next->isPlayerEntry() == CombatObject::HackStateStorage[ArrowVolley::StateKeyIsCasterOnEnemyTeam].asBool())
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), std::abs(ArrowVolley::Damage), AbilityType::Passive, true));
			}
		}
	}));
}

NO_OPTIMIZE void ArrowVolley::compareTeam(TimelineEntry* entry)
{
	static volatile int isOnEnemyTeamLocal;

	isOnEnemyTeamLocal = entry->isPlayerEntry() ? 1 : -1;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM(mov ZAX, 0);
	ASM_MOV_REG_VAR(eax, isOnEnemyTeamLocal);
	ASM(mov ZBX, 0);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM);
	ASM(test ZAX, ZAX);
	ASM(jns skipAssign);
	ASM(mov ZBX, 1);
	ASM(skipAssign:);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(isOnEnemyTeamLocal, eax);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	CombatObject::HackStateStorage[ArrowVolley::StateKeyIsCasterOnEnemyTeam] = Value((isOnEnemyTeamLocal != 0) ? false : true);
}
END_NO_OPTIMIZE
