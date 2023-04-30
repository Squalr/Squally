#include "FireRain.h"

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
#include "Objects/Platformer/Combat/Abilities/FireRain/FireRainGenericPreview.h"
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

const int FireRain::TickCount = 6;
const int FireRain::Damage = 6;
const float FireRain::TimeBetweenTicks = 0.75f;
const float FireRain::StartDelay = 0.25f;
const std::string FireRain::StateKeyIsCasterOnEnemyTeam = "ANTI_OPTIMIZE_STATE_KEY_DAMAGE_TAKEN";

const std::string FireRain::HackIdentifierFireRainTeamCompare = "bat-swarm-team";

FireRain* FireRain::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	FireRain* instance = new FireRain(caster, target);

	instance->autorelease();

	return instance;
}

FireRain::FireRain(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, true)
{
	for (int index = 0; index < 8; index++)
	{
		ValueMap valueMap;
		SmartAnimationSequenceNode* meteor = SmartAnimationSequenceNode::create();

		this->meteorPool.push_back(meteor);
		this->meteorCooldowns.push_back(float(index) * 0.4f);

		this->addChild(meteor);
	}
}

FireRain::~FireRain()
{
}

void FireRain::onEnter()
{
	super::onEnter();

	this->runFireRain();
	
	CombatEvents::TriggerHackableCombatCue();
}

void FireRain::update(float dt)
{
	super::update(dt);

	this->updateAnimation(dt);
}

Vec2 FireRain::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void FireRain::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COMPARE_TEAM,
			HackableCode::HackableCodeInfo(
				FireRain::HackIdentifierFireRainTeamCompare,
				Strings::Menus_Hacking_Abilities_Abilities_FireRain_CompareTeam::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_FireBolts,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Abilities_FireRain_RegisterXmm3::create()
					},
					{
						HackableCode::Register::xmm4, Strings::Menus_Hacking_Abilities_Abilities_FireRain_RegisterXmm4::create()
					},
				},
				int(HackFlags::None),
				FireRain::StartDelay + FireRain::TimeBetweenTicks * float(FireRain::TickCount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Abilities_FireRain_CommentCompare::create(),
							ConstantString::create("comiss xmm3, xmm4\n"),
							ConstantString::create("je skipCode\n"),
							ConstantString::create("mov eax, 1\n"),
							ConstantString::create("skipCode:\n\n"),
							Strings::Menus_Hacking_Abilities_Abilities_FireRain_CommentHint::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())
						})
						, // x64
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Abilities_FireRain_CommentCompare::create(),
							ConstantString::create("comiss xmm3, xmm4\n"),
							ConstantString::create("je skipCode\n"),
							ConstantString::create("mov rax, 1\n"),
							ConstantString::create("skipCode:\n\n"),
							Strings::Menus_Hacking_Abilities_Abilities_FireRain_CommentHint::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())
						})
					),
				},
				true
			)
		},
	};

	std::vector<HackableCode*> hackables = CREATE_HACKABLES(FireRain::compareTeam, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* FireRain::createDefaultPreview()
{
	return FireRainGenericPreview::create();
}

void FireRain::runFireRain()
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int index = 0; index < FireRain::TickCount; index++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_FireBolts);

		icon->setScale(0.5f);

		this->meteorPool[index]->playAnimation(FXResources::FireBomb_FireBomb_0000, 0.05f, true);

		timelineEvents.push_back(TimelineEvent::create(
				this->caster,
				icon,
				FireRain::TimeBetweenTicks * float(index) + FireRain::StartDelay, [=]()
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

void FireRain::updateAnimation(float dt)
{
	static const float VarianceX = 768.0f;
	static const float FallDistance = -1280.0f;
	static const float PixelsPerSecond = 768.0f;
	static const float Duration = std::abs(FallDistance) / PixelsPerSecond;

	float totalDuration = FireRain::StartDelay + FireRain::TimeBetweenTicks * float(FireRain::TickCount);

	for (int index = 0; index < int(this->meteorCooldowns.size()); index++)
	{
		if (!this->timelinePaused)
		{
			this->meteorCooldowns[index] -= dt;
			this->meteorPool[index]->setPositionY(this->meteorPool[index]->getPositionY() - dt * PixelsPerSecond);
		}

		if (this->meteorCooldowns[index] <= 0.0f)
		{
			this->meteorPool[index]->setOpacity(0);
			this->meteorPool[index]->setPosition(Vec2(RandomHelper::random_real(-VarianceX, VarianceX), 0.0f));
			this->meteorPool[index]->runAction(FadeTo::create(0.25f, 255));
			this->meteorPool[index]->playAnimation(FXResources::FireOrb_ready_attack_00, 0.05f, true);

			this->meteorCooldowns[index] = Duration;
		}
	}
}

void FireRain::damageOtherTeam()
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
			if (next->isPlayerEntry() == CombatObject::HackStateStorage[FireRain::StateKeyIsCasterOnEnemyTeam].asBool())
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), std::abs(FireRain::Damage), AbilityType::Passive, true));
			}
		}
	}));
}

NO_OPTIMIZE void FireRain::compareTeam(TimelineEntry* entry)
{
	static volatile float isOnEnemyTeamLocal = 0.0f;
	static volatile float* isOnEnemyTeamLocalPtr = nullptr;
	static volatile float constZero = 0.0f;
	static volatile float* constZeroPtr = nullptr;

	isOnEnemyTeamLocal = entry->isPlayerEntry() ? 0.0f : 1.0f;
	isOnEnemyTeamLocalPtr = &isOnEnemyTeamLocal;
	constZero = 0.0f;
	constZeroPtr = &constZero;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);
	ASM(push ZCX);

	ASM(mov ZAX, 0);
	ASM_MOV_REG_VAR(ebx, isOnEnemyTeamLocalPtr);
	ASM_MOV_REG_VAR(ecx, constZeroPtr);

	ASM(movss xmm3, dword ptr [ZBX]);
	ASM(movss xmm4, dword ptr [ZCX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_COMPARE_TEAM);
	ASM(comiss xmm3, xmm4);
	ASM(je skipCodeFireRain);
	ASM(mov eax, 1);
	ASM(skipCodeFireRain:);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(isOnEnemyTeamLocal, eax);

	ASM(pop ZCX);
	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	CombatObject::HackStateStorage[FireRain::StateKeyIsCasterOnEnemyTeam] = Value((isOnEnemyTeamLocal == 0) ? false : true);
}
END_NO_OPTIMIZE
