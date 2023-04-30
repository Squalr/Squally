#include "BatSwarm.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/Critters/Bat.h"
#include "Objects/Platformer/Combat/Abilities/BatSwarm/BatSwarmGenericPreview.h"
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

const int BatSwarm::TickCount = 6;
const int BatSwarm::Damage = 8;
const float BatSwarm::TimeBetweenTicks = 0.75f;
const float BatSwarm::StartDelay = 0.25f;
const std::string BatSwarm::StateKeyIsCasterOnEnemyTeam = "ANTI_OPTIMIZE_STATE_KEY_DAMAGE_TAKEN";

const std::string BatSwarm::HackIdentifierBatSwarmTeamCompare = "bat-swarm-team";

BatSwarm* BatSwarm::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	BatSwarm* instance = new BatSwarm(caster, target);

	instance->autorelease();

	return instance;
}

BatSwarm::BatSwarm(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, true)
{
	for (int index = 0; index < 8; index++)
	{
		ValueMap valueMap;
		PlatformerEntity* bat = Bat::deserialize(valueMap);

		// Arrows are assumed to point up
		bat->setRotation(180.0f);
		bat->setOpacity(0);

		this->batPool.push_back(bat);
		this->batCooldowns.push_back(float(index) * 0.4f);

		this->addChild(bat);
	}
}

BatSwarm::~BatSwarm()
{
}

void BatSwarm::onEnter()
{
	super::onEnter();

	this->runBatSwarm();
	
	CombatEvents::TriggerHackableCombatCue();
}

void BatSwarm::update(float dt)
{
	super::update(dt);

	this->updateAnimation(dt);
}

Vec2 BatSwarm::getButtonOffset()
{
	return Vec2(0.0f, -768.0f);
}

void BatSwarm::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COMPARE_TEAM,
			HackableCode::HackableCodeInfo(
				BatSwarm::HackIdentifierBatSwarmTeamCompare,
				Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_CompareTeam::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Bats,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_RegisterEax::create()
					},
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_RegisterEcx::create()
					},
				},
				int(HackFlags::None),
				BatSwarm::StartDelay + BatSwarm::TimeBetweenTicks * float(BatSwarm::TickCount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_CommentCompare::create()),
							ConstantString::create("jecxz skipCode\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_CommentApplyDamage::create()),
							ConstantString::create("mov eax, 1\n"),
							ConstantString::create("skipCode:\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_CommentHint::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zcx))),
							ConstantString::create("\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJecxz::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentEcx::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentZ::create())
						})
						, // x64
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_CommentCompare::create()),
							ConstantString::create("jecxz skipCode\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_CommentApplyDamage::create()),
							ConstantString::create("mov rax, 1\n"),
							ConstantString::create("skipCode:\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_CommentHint::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zax))),
							ConstantString::create("\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJecxz::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentEcx::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentZ::create())
						})
					),
				},
				true
			)
		},
	};

	std::vector<HackableCode*> hackables = CREATE_HACKABLES(BatSwarm::compareTeam, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* BatSwarm::createDefaultPreview()
{
	return BatSwarmGenericPreview::create();
}

void BatSwarm::runBatSwarm()
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int index = 0; index < BatSwarm::TickCount; index++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_Bats);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->caster,
				icon,
				BatSwarm::TimeBetweenTicks * float(index) + BatSwarm::StartDelay, [=]()
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

void BatSwarm::updateAnimation(float dt)
{
	static const float VarianceX = 768.0f;
	static const float FallDistance = -1280.0f;
	static const float PixelsPerSecond = 768.0f;
	static const float Duration = std::abs(FallDistance) / PixelsPerSecond;

	float totalDuration = BatSwarm::StartDelay + BatSwarm::TimeBetweenTicks * float(BatSwarm::TickCount);

	for (int index = 0; index < int(this->batCooldowns.size()); index++)
	{
		if (!this->timelinePaused)
		{
			this->batCooldowns[index] -= dt;
			this->batPool[index]->setPositionY(this->batPool[index]->getPositionY() - dt * PixelsPerSecond);
		}

		if (this->batCooldowns[index] <= 0.0f)
		{
			this->batPool[index]->setOpacity(0);
			this->batPool[index]->setPosition(Vec2(RandomHelper::random_real(-VarianceX, VarianceX), 0.0f));
			this->batPool[index]->runAction(FadeTo::create(0.25f, 255));

			this->batCooldowns[index] = Duration;
		}
	}
}

void BatSwarm::damageOtherTeam()
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
			if (next->isPlayerEntry() == CombatObject::HackStateStorage[BatSwarm::StateKeyIsCasterOnEnemyTeam].asBool())
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), std::abs(BatSwarm::Damage), AbilityType::Passive, true));
			}
		}
	}));
}

NO_OPTIMIZE void BatSwarm::compareTeam(TimelineEntry* entry)
{
	static volatile int isOnEnemyTeamLocal;

	isOnEnemyTeamLocal = entry->isPlayerEntry() ? 0 : 1;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZCX);

	ASM_MOV_REG_VAR(ZCX, isOnEnemyTeamLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM);
	ASM(jecxz skipCodeBatSwarm);
	ASM(mov ZAX, 1);
	ASM(skipCodeBatSwarm:);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(isOnEnemyTeamLocal, eax);

	ASM(pop ZCX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	CombatObject::HackStateStorage[BatSwarm::StateKeyIsCasterOnEnemyTeam] = Value((isOnEnemyTeamLocal == 0) ? false : true);
}
END_NO_OPTIMIZE
