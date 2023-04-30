#include "Leech.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Leech/LeechGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_LEECH 1

const std::string Leech::LeechIdentifier = "leech";
const int Leech::TickCount = 5;
const int Leech::DrainAmountMax = 8;
const float Leech::TimeBetweenTicks = 0.5f;
const float Leech::StartDelay = 0.25f;

Leech* Leech::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Leech* instance = new Leech(caster, target);

	instance->autorelease();

	return instance;
}

Leech::Leech(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordGlowBlue, AbilityType::Shadow, BuffData())
{
	this->drainEffect = SmartAnimationSequenceNode::create(FXResources::HealMP_Heal_0000);
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->drainSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);

	this->drainEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	this->addChild(this->drainEffect);
	this->addChild(this->impactSound);
	this->addChild(this->drainSound);
}

Leech::~Leech()
{
}

void Leech::onEnter()
{
	super::onEnter();

	this->runLeech();

	CombatEvents::TriggerHackableCombatCue();
}

void Leech::initializePositions()
{
	super::initializePositions();

	this->drainEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 12.0f);
}

void Leech::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_LEECH,
			HackableCode::HackableCodeInfo(
				Leech::LeechIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Leech_Leech::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_SwordGlowBlue,
				LazyNode<HackablePreview>::create([=](){ return LeechGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Debuffs_Leech_RegisterEdi::create(),
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Leech_RegisterEsi::create(),
					}
				},
				int(HackFlags::None),
				Leech::StartDelay + Leech::TimeBetweenTicks * float(Leech::TickCount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Leech_CommentRng::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zsi))),
							ConstantString::create("cmp esi, 0\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Leech_CommentJz::create()),
							ConstantString::create("jz skipCode\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Leech_CommentApplyDamage::create()),
							ConstantString::create("mov edi, 5\n"),
							ConstantString::create("skipCode:\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJz::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentZ::create())
						})
						, // x64
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Leech_CommentRng::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zsi))),
							ConstantString::create("cmp rsi, 0\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Leech_CommentJz::create()),
							ConstantString::create("jz skipCode\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Leech_CommentApplyDamage::create()),
							ConstantString::create("mov rdi, 5\n"),
							ConstantString::create("skipCode:\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJz::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentZ::create())
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Leech::runLeechTick, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Leech::runLeech()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int tickIndex = 0; tickIndex < Leech::TickCount; tickIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_BloodGoblet);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				Leech::TimeBetweenTicks * float(tickIndex) + Leech::StartDelay, [=]()
			{
				if (!this->drainEffect->isPlayingAnimation())
				{
					this->drainEffect->playAnimation(FXResources::HealMP_Heal_0000, 0.05f);
				}
				
				this->runLeechTick();
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

NO_OPTIMIZE void Leech::runLeechTick()
{
	static volatile int drainAmount = 0;
	static volatile int rng = 0;

	drainAmount = 0;
	rng = RandomHelper::random_int(0, 1);

	ASM_PUSH_EFLAGS()
	ASM(push ZDI);
	ASM(push ZSI);

	ASM(mov ZDI, 0);
	ASM_MOV_REG_VAR(ZDI, rng);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_LEECH);
	ASM(cmp ZSI, 0);
	ASM(jz skipLeechCode);
	ASM(mov ZDI, 5); // Leech::DrainAmount
	ASM(skipLeechCode:);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(drainAmount, edi);

	ASM(pop ZSI);
	ASM(pop ZDI);
	ASM_POP_EFLAGS()

	bool overflowedMin = drainAmount <= -Leech::DrainAmountMax;
	bool overflowedMax = drainAmount >= Leech::DrainAmountMax;
	drainAmount = MathUtils::clamp(drainAmount, -Leech::DrainAmountMax, Leech::DrainAmountMax);

	this->drainSound->play();
	CombatEvents::TriggerManaDrain(CombatEvents::ManaRestoreOrDrainArgs(this->caster, this->owner, drainAmount, this->abilityType, true, overflowedMin, overflowedMax));
	CombatEvents::TriggerManaRestore(CombatEvents::ManaRestoreOrDrainArgs(this->owner, this->caster, drainAmount, this->abilityType, true, overflowedMax, overflowedMin));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
