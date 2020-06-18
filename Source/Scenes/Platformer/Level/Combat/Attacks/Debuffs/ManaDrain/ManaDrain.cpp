#include "ManaDrain.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/ManaDrain/ManaDrainGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_MANA_DRAIN 1

const std::string ManaDrain::ManaDrainIdentifier = "mana-drain";
const int ManaDrain::DrainAmount = 7;
const float ManaDrain::TimeBetweenTicks = 0.75f;
const float ManaDrain::StartDelay = 0.5f;

ManaDrain* ManaDrain::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ManaDrain* instance = new ManaDrain(caster, target);

	instance->autorelease();

	return instance;
}

ManaDrain::ManaDrain(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_ManaSkull, AbilityType::Shadow, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create(FXResources::Heal_Heal_0000);
	this->drainAmount = ManaDrain::DrainAmount;
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

ManaDrain::~ManaDrain()
{
}

void ManaDrain::onEnter()
{
	super::onEnter();

	this->runManaDrain();

	CombatEvents::TriggerHackableCombatCue();
}

void ManaDrain::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f - this->owner->getEntityCenterPoint().y));
}

void ManaDrain::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_MANA_DRAIN,
			HackableCode::HackableCodeInfo(
				ManaDrain::ManaDrainIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_ManaDrain::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_ManaSkull,
				ManaDrainGenericPreview::create(),
				{
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_RegisterEcx::create(),
					},
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_RegisterEdx::create(),
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_CommentCompare::create()) +
						"cmp ecx, 4\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_CommentConditionalMov::create()) +
						"cmovge esi, edx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovge::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentC::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentMov::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentLe::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_CommentFinale::create()) +
						"\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_CommentHint::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create()))
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_CommentCompare::create()) +
						"cmp rcx, 4\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_CommentConditionalMov::create()) +
						"cmovge rsi, rdx\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentCmovge::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentC::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentMov::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Cmov_CommentLe::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_CommentFinale::create()) +
						"\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_ManaDrain_CommentHint::create()
							->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsi::create()))
					),
				},
				true
			)
		},
	};

	auto restoreFunc = &ManaDrain::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void ManaDrain::runManaDrain()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < this->drainAmount; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_ManaSkull);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				ManaDrain::TimeBetweenTicks * float(healIndex) + ManaDrain::StartDelay, [=]()
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

NO_OPTIMIZE void ManaDrain::runRestoreTick()
{
	static volatile int drainAmount = 0;
	static volatile int currentMana = 0;

	drainAmount = 0;
	currentMana = this->owner->getRuntimeStateOrDefaultInt(StateKeys::Mana, 0);

	ASM_PUSH_EFLAGS();
	ASM(push ZCX);
	ASM(push ZDX);
	ASM(push ZSI);

	ASM_MOV_REG_VAR(ZCX, currentMana);
	ASM(mov ZSI, 0);
	ASM(mov ZDX, -1);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_MANA_DRAIN);
	ASM(cmp ZCX, 4);
	ASM(cmovge ZSI, ZDX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(drainAmount, ZSI);

	ASM(pop ZSI);
	ASM(pop ZDX);
	ASM(pop ZCX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	drainAmount = MathUtils::clamp(drainAmount, -3, 3);

	this->healSound->play();
	CombatEvents::TriggerManaDrain(CombatEvents::ManaRestoreOrDrainArgs(this->caster, this->owner, drainAmount, this->abilityType));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
