#include "ShadowBomb.h"

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
#include "Objects/Platformer/Combat/Abilities/ShadowBomb/ShadowBombGenericPreview.h"
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

#define LOCAL_FUNC_ID_SHADOW_BOMB 11

const std::string ShadowBomb::HackIdentifierShadowBomb = "shadow-bomb";

ShadowBomb* ShadowBomb::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ShadowBomb* instance = new ShadowBomb(caster, target);

	instance->autorelease();

	return instance;
}

ShadowBomb::ShadowBomb(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, true)
{
	this->animationNode = nullptr; // TODO

	this->addChild(this->animationNode);
}

ShadowBomb::~ShadowBomb()
{
}

void ShadowBomb::onEnter()
{
	super::onEnter();

	this->runShadowBomb(nullptr);
	
	CombatEvents::TriggerHackableCombatCue();
}

void ShadowBomb::update(float dt)
{
	super::update(dt);
}

Vec2 ShadowBomb::getButtonOffset()
{
	return Vec2(0.0f, 96.0f);
}

void ShadowBomb::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_COMPARE_TEAM,
			HackableCode::HackableCodeInfo(
				ShadowBomb::HackIdentifierShadowBomb,
				Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_CompareTeam::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_SpellImpactPurple,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Abilities_ArrowRain_RegisterEax::create()
					},
				},
				int(HackFlags::None),
				12.0f,
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

	auto func = &ShadowBomb::dealDamage;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* ShadowBomb::createDefaultPreview()
{
	return ShadowBombGenericPreview::create();
}

void ShadowBomb::runShadowBomb(TimelineEntry* target)
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	Sprite* icon = Sprite::create(UIResources::Menus_Icons_SpellImpactPurple);

	icon->setScale(0.5f);

	timelineEvents.push_back(TimelineEvent::create(
			this->caster,
			icon,
			5.0f, [=]()
		{
			this->dealDamage(target);
		})
	);

	CombatEvents::TriggerRegisterTimelineEventGroup(CombatEvents::RegisterTimelineEventGroupArgs(
		TimelineEventGroup::create(timelineEvents, nullptr, this->caster, [=]()
		{
			this->despawn();
		})
	));
}

NO_OPTIMIZE void ShadowBomb::dealDamage(TimelineEntry* target)
{
	static volatile int isOnEnemyTeamLocal;

	isOnEnemyTeamLocal = target->isPlayerEntry() ? 0 : 1;

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
}
END_NO_OPTIMIZE
