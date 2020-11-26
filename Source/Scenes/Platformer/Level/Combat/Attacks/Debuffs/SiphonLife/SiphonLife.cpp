#include "SiphonLife.h"

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
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/SiphonLife/SiphonLifeGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SIPHON_LIFE 1

const std::string SiphonLife::SiphonLifeIdentifier = "siphon-life";
const int SiphonLife::HealAmount = 7;
const float SiphonLife::TimeBetweenTicks = 0.5f;
const float SiphonLife::StartDelay = 0.25f;

SiphonLife* SiphonLife::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	SiphonLife* instance = new SiphonLife(caster, target);

	instance->autorelease();

	return instance;
}

SiphonLife::SiphonLife(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_BloodGoblet, AbilityType::Shadow, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create(FXResources::Heal_Heal_0000);
	this->healAmount = SiphonLife::HealAmount;
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

SiphonLife::~SiphonLife()
{
}

void SiphonLife::onEnter()
{
	super::onEnter();

	this->runSiphonLife();

	CombatEvents::TriggerHackableCombatCue();
}

void SiphonLife::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f - this->owner->getEntityCenterPoint().y));
}

void SiphonLife::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_SIPHON_LIFE,
			HackableCode::HackableCodeInfo(
				SiphonLife::SiphonLifeIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_SiphonLife::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_BloodGoblet,
				LazyNode<HackablePreview>::create([=](){ return SiphonLifeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_RegisterEdi::create(),
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_RegisterEsi::create(),
					}
				},
				int(HackFlags::None),
				SiphonLife::StartDelay + SiphonLife::TimeBetweenTicks * float(SiphonLife::HealAmount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_CommentGain::create()) +
						"inc edi\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_CommentDrain::create()) +
						"dec esi\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_CommentReverse::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_CommentGain::create()) +
						"inc rdi\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_CommentDrain::create()) +
						"dec rsi\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_SiphonLife_CommentReverse::create())
					),
				},
				true
			)
		},
	};

	auto restoreFunc = &SiphonLife::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void SiphonLife::runSiphonLife()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < this->healAmount; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_BloodGoblet);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				SiphonLife::TimeBetweenTicks * float(healIndex) + SiphonLife::StartDelay, [=]()
			{
				if (!this->healEffect->isPlayingAnimation())
				{
					this->healEffect->playAnimation(FXResources::Heal_Heal_0000, 0.05f);
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

NO_OPTIMIZE void SiphonLife::runRestoreTick()
{
	static volatile int drainAmount = 0;
	static volatile int gainAmount = 0;

	drainAmount = 0;
	gainAmount = 0;

	ASM(push ZDI);
	ASM(push ZSI);

	ASM(mov ZDI, 0);
	ASM(mov ZSI, 0);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SIPHON_LIFE);
	ASM(inc ZDI);
	ASM(dec ZSI);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(drainAmount, edi);
	ASM_MOV_VAR_REG(gainAmount, esi);

	ASM(pop ZSI);
	ASM(pop ZDI);

	drainAmount = MathUtils::clamp(drainAmount, -8, 8);
	gainAmount = MathUtils::clamp(gainAmount, -8, 8);

	this->healSound->play();
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->owner, this->caster, drainAmount, this->abilityType));
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, gainAmount, this->abilityType));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
