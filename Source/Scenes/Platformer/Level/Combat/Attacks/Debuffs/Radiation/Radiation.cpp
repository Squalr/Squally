#include "Radiation.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Radiation/RadiationGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RADIATION 1

const std::string Radiation::RadiationIdentifier = "radiation";
const int Radiation::DamageAmount = 5;
const int Radiation::DamageAmountMax = 8;
const float Radiation::TimeBetweenTicks = 0.5f;
const float Radiation::StartDelay = 0.25f;

Radiation* Radiation::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Radiation* instance = new Radiation(caster, target);

	instance->autorelease();

	return instance;
}

Radiation::Radiation(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Radiation, AbilityType::Shadow, BuffData())
{
	this->healAmount = Radiation::DamageAmount;
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Recharge1);

	this->addChild(this->healSound);
}

Radiation::~Radiation()
{
}

void Radiation::onEnter()
{
	super::onEnter();

	this->runRadiation();

	CombatEvents::TriggerHackableCombatCue();
}

void Radiation::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f - this->owner->getEntityCenterPoint().y));
}

void Radiation::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RADIATION,
			HackableCode::HackableCodeInfo(
				Radiation::RadiationIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Radiation_Radiation::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_Radiation,
				LazyNode<HackablePreview>::create([=](){ return RadiationGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdi, Strings::Menus_Hacking_Abilities_Debuffs_Radiation_RegisterEdi::create(), HackableDataType::Int32
					},
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Radiation_RegisterEsi::create(), HackableDataType::Int32
					}
				},
				int(HackFlags::None),
				Radiation::StartDelay + Radiation::TimeBetweenTicks * float(Radiation::DamageAmount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Radiation_CommentRng::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zsi))),
							ConstantString::create("cmp esi, 0\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Radiation_CommentJnz::create()),
							ConstantString::create("jnz radiation\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Radiation_CommentJmp::create()),
							ConstantString::create("jmp skipCode\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Radiation_CommentApplyDamage::create()),
							ConstantString::create("mov edi, 5\n"), // Radiation::DamageAmount
							ConstantString::create("radiation:\n"),
							ConstantString::create("skipCode:\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJnz::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentNz::create())
						})
						, // x64
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Radiation_CommentRng::create()
								->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zsi))),
							ConstantString::create("cmp rsi, 0\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Radiation_CommentJnz::create()),
							ConstantString::create("jnz radiation\n\n"),
							ConstantString::create("jmp skipCode\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Radiation_CommentApplyDamage::create()),
							ConstantString::create("mov rdi, 5\n"), // Radiation::DamageAmount
							ConstantString::create("radiation:\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_Radiation_CommentJmp::create()),
							ConstantString::create("skipCode:\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJnz::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJ::create()),
							COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentNz::create())
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Radiation::runRadiationTick, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Radiation::runRadiation()
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < this->healAmount; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_Radiation);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				Radiation::TimeBetweenTicks * float(healIndex) + Radiation::StartDelay, [=]()
			{
				this->runRadiationTick();
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

NO_OPTIMIZE void Radiation::runRadiationTick()
{
	static volatile int drainAmount = 0;
	static volatile int rng = 0;

	drainAmount = 0;
	rng = RandomHelper::random_int(0, 1);

	ASM_PUSH_EFLAGS()
	ASM(push ZDI);
	ASM(push ZSI);

	ASM(mov ZDI, 0);
	ASM_MOV_REG_VAR(esi, rng);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RADIATION);
	ASM(cmp ZSI, 0);
	ASM(jnz radiation);
	ASM(jmp radiationSkip);
	ASM(radiation:);
	ASM(mov ZDI, 5); // Radiation::DamageAmount
	ASM(radiationSkip:);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(drainAmount, edi);

	ASM(pop ZSI);
	ASM(pop ZDI);
	ASM_POP_EFLAGS()

	drainAmount = MathUtils::clamp(drainAmount, -Radiation::DamageAmountMax, Radiation::DamageAmountMax);

	this->healSound->play();
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, drainAmount, this->abilityType));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
