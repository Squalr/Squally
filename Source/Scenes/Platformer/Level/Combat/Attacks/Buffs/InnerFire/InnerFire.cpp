#include "InnerFire.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/InnerFire/InnerFireGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INNER_FIRE 1

const std::string InnerFire::InnerFireIdentifier = "inner-fire";
const float InnerFire::TimeBetweenTicks = 1.0f;
const int InnerFire::HealTicks = 5;
const float InnerFire::StartDelay = 0.15f;
const int InnerFire::MaxHealing = 255;

InnerFire* InnerFire::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	InnerFire* instance = new InnerFire(caster, target);

	instance->autorelease();

	return instance;
}

InnerFire::InnerFire(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SkullLavaEyes, AbilityType::Fire, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create();
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);
	
	this->healEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

InnerFire::~InnerFire()
{
}

void InnerFire::onEnter()
{
	super::onEnter();

	this->runInnerFire();

	CombatEvents::TriggerHackableCombatCue();
}

void InnerFire::initializePositions()
{
	super::initializePositions();
	
	this->healEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 12.0f);
}

void InnerFire::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_INNER_FIRE,
			HackableCode::HackableCodeInfo(
				InnerFire::InnerFireIdentifier,
				Strings::Menus_Hacking_Abilities_Abilities_InnerFire_InnerFire::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_SkullLavaEyes,
				LazyNode<HackablePreview>::create([=](){ return InnerFireGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Abilities_InnerFire_RegisterEcx::create()
					},
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Abilities_InnerFire_RegisterEdx::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_InnerFire_CommentXchg::create()) +
						std::string("xchg ecx, edx\n")
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_InnerFire_CommentXchg::create()) +
						std::string("xchg rcx, rdx\n")
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(InnerFire::runRestoreTick, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void InnerFire::runInnerFire()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < InnerFire::HealTicks; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ArrowUp);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				InnerFire::TimeBetweenTicks * float(healIndex) + InnerFire::StartDelay, [=]()
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

NO_OPTIMIZE void InnerFire::runRestoreTick()
{
	static volatile int healingSelf = 4;
	static volatile int healingOther = -4;

	ASM_PUSH_EFLAGS()
	ASM(push ZCX);
	ASM(push ZDX);

	ASM_MOV_REG_VAR(ZDX, healingSelf);
	ASM_MOV_REG_VAR(ZCX, healingOther);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INNER_FIRE);
	ASM(xchg ZCX, ZDX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(healingSelf, ZCX);
	ASM_MOV_VAR_REG(healingOther, ZDX);

	ASM(pop ZDX);
	ASM(pop ZCX);
	ASM_POP_EFLAGS()

	this->healSound->play();

	int delta = MathUtils::clamp((int)healingSelf, -InnerFire::MaxHealing, InnerFire::MaxHealing);
	bool overflowedMin = delta == -InnerFire::MaxHealing;
	bool overflowedMax = delta == InnerFire::MaxHealing;
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, delta, this->abilityType, true, overflowedMin, overflowedMax));

	delta = MathUtils::clamp((int)healingOther, -InnerFire::MaxHealing, InnerFire::MaxHealing);
	overflowedMin = delta == -InnerFire::MaxHealing;
	overflowedMax = delta == InnerFire::MaxHealing;
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->owner, this->caster, delta, this->abilityType, true, overflowedMin, overflowedMax));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
