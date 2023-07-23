#include "HotPotato.h"

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
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/HotPotato/HotPotatoGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_HOT_POTATO 1

const std::string HotPotato::HotPotatoIdentifier = "hot-potato";
const int HotPotato::HealAmount = 6;
const float HotPotato::TimeBetweenTicks = 1.0f;
const float HotPotato::StartDelay = 0.25f;

HotPotato* HotPotato::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	HotPotato* instance = new HotPotato(caster, target);

	instance->autorelease();

	return instance;
}

HotPotato::HotPotato(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_HotPotato, AbilityType::Physical, BuffData())
{
	this->healEffect = SmartAnimationSequenceNode::create(FXResources::Heal_Heal_0000);
	this->healAmount = HotPotato::HealAmount;
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Ding1);

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

HotPotato::~HotPotato()
{
}

void HotPotato::onEnter()
{
	super::onEnter();

	this->runHotPotato();

	CombatEvents::TriggerHackableCombatCue();
}

void HotPotato::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f - this->owner->getEntityCenterPoint().y));
}

void HotPotato::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HOT_POTATO,
			HackableCode::HackableCodeInfo(
				HotPotato::HotPotatoIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_HotPotato_HotPotato::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_HotPotato,
				LazyNode<HackablePreview>::create([=](){ return HotPotatoGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_HotPotato_RegisterEsi::create(),
					},
				},
				int(HackFlags::None),
				HotPotato::StartDelay + HotPotato::TimeBetweenTicks * float(HotPotato::HealAmount),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_HotPotato_CommentDrain::create()),
							ConstantString::create("dec esi\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_HotPotato_CommentHint::create())
						})
						, // x64
						ConcatString::create({
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_HotPotato_CommentDrain::create()),
							ConstantString::create("dec rsi\n\n"),
							COMMENT(Strings::Menus_Hacking_Abilities_Debuffs_HotPotato_CommentHint::create())
						})
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(HotPotato::runRestoreTick, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void HotPotato::onAfterDamageDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
	if (damageOrHealing != nullptr && damageOrHealing->target != nullptr)
	{
		damageOrHealing->target->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(HotPotato::create(owner, damageOrHealing->target));
		});
	}
	
	this->removeBuff();
}

void HotPotato::runHotPotato()
{
	this->impactSound->play();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < this->healAmount; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_HotPotato);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				HotPotato::TimeBetweenTicks * float(healIndex) + HotPotato::StartDelay, [=]()
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

NO_OPTIMIZE void HotPotato::runRestoreTick()
{
	static volatile int drainAmount = 0;

	drainAmount = 0;

	ASM_PUSH_EFLAGS()
	ASM(push ZSI);

	ASM(mov ZSI, 0);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HOT_POTATO);
	ASM(dec ZSI);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(drainAmount, esi);

	ASM(pop ZSI);
	ASM_POP_EFLAGS()

	drainAmount = MathUtils::clamp(drainAmount, -8, 8);

	this->healSound->play();
	CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->owner, drainAmount, this->abilityType));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
