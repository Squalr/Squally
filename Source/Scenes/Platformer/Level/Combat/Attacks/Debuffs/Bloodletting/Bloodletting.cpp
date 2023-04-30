#include "Bloodletting.h"

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
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Bloodletting/BloodlettingGenericPreview.h"
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

const std::string Bloodletting::BloodlettingIdentifier = "bloodletting";
const int Bloodletting::DamageAmount = 5;
const int Bloodletting::DamageAmountMax = 8;
const float Bloodletting::TimeBetweenTicks = 1.0f;
const float Bloodletting::StartDelay = 0.25f;

Bloodletting* Bloodletting::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Bloodletting* instance = new Bloodletting(caster, target);

	instance->autorelease();

	return instance;
}

Bloodletting::Bloodletting(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Stab, AbilityType::Shadow, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create(FXResources::Heal_Heal_0000);
	this->healAmount = Bloodletting::DamageAmount;
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

Bloodletting::~Bloodletting()
{
}

void Bloodletting::onEnter()
{
	super::onEnter();

	this->runBloodletting();

	CombatEvents::TriggerHackableCombatCue();
}

void Bloodletting::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f - this->owner->getEntityCenterPoint().y));
}

void Bloodletting::registerHackables()
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
				Bloodletting::BloodlettingIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_Bloodletting::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_Stab,
				LazyNode<HackablePreview>::create([=](){ return BloodlettingGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_RegisterEbx::create(),
					},
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_RegisterEdx::create(),
					}
				},
				int(HackFlags::None),
				Bloodletting::StartDelay + Bloodletting::TimeBetweenTicks * float(Bloodletting::DamageAmount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_CommentRng::create(),
							ConstantString::create("test ebx, ebx\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_CommentJs::create(),
							ConstantString::create("js bloodletting\n\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_CommentJmp::create(),
							ConstantString::create("jmp skipCode\n\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_CommentApplyDamage::create(),
							ConstantString::create("bloodletting:\n"),
							ConstantString::create("mov edi, 5\n"), // Bloodletting::DamageAmount
							ConstantString::create("skipCode:\n\n")
						})
						, // x64
						ConcatString::create({
							Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_CommentRng::create(),
							ConstantString::create("test rbx, rbx\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_CommentJs::create(),
							ConstantString::create("js bloodletting\n\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_CommentJmp::create(),
							ConstantString::create("jmp skipCode\n\n"),
							Strings::Menus_Hacking_Abilities_Debuffs_Bloodletting_CommentApplyDamage::create(),
							ConstantString::create("bloodletting:\n"),
							ConstantString::create("mov rdi, 5\n"), // Bloodletting::DamageAmount
							ConstantString::create("skipCode:\n\n")
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(Bloodletting::runBloodlettingTick, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void Bloodletting::runBloodletting()
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
				Bloodletting::TimeBetweenTicks * float(healIndex) + Bloodletting::StartDelay, [=]()
			{
				if (!this->healEffect->isPlayingAnimation())
				{
					this->healEffect->playAnimation(FXResources::Heal_Heal_0000, 0.05f);
				}
				
				this->runBloodlettingTick();
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

NO_OPTIMIZE void Bloodletting::runBloodlettingTick()
{
	static volatile int drainAmount = 0;
	static volatile int rng = 0;

	drainAmount = 0;
	rng = RandomHelper::random_int(-100, 100);

	ASM_PUSH_EFLAGS()
	ASM(push ZBX);
	ASM(push ZDX);

	ASM_MOV_REG_VAR(ebx, rng);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RADIATION);
	ASM(test ZBX, ZBX);
	ASM(jns bloodletting);
	ASM(jmp bloodlettingSkip);
	ASM(bloodletting:);
	ASM(mov ZDX, 5); // Bloodletting::DamageAmount
	ASM(bloodlettingSkip:);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(drainAmount, edi);

	ASM(pop ZDX);
	ASM(pop ZBX);
	ASM_POP_EFLAGS()

	drainAmount = MathUtils::clamp(drainAmount, -Bloodletting::DamageAmountMax, Bloodletting::DamageAmountMax);

	this->healSound->play();
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, drainAmount, this->abilityType));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
