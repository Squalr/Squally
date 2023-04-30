#include "HeavyBlade.h"

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
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/HeavyBlade/HeavyBladeGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_HEAVYBLADE 1

const std::string HeavyBlade::HeavyBladeIdentifier = "heavy-blade";

const int HeavyBlade::MinMultiplier = -1;
const int HeavyBlade::MaxMultiplier = 2;
const float HeavyBlade::Duration = 12.0f;

// Static to prevent GCC optimization issues
volatile int HeavyBlade::currentDamageDealt = 0;

HeavyBlade* HeavyBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	HeavyBlade* instance = new HeavyBlade(caster, target);

	instance->autorelease();

	return instance;
}

HeavyBlade::HeavyBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_Shovel, AbilityType::Physical, BuffData(HeavyBlade::Duration, HeavyBlade::HeavyBladeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageDealt = 0;

	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->spellAura);
}

HeavyBlade::~HeavyBlade()
{
}

void HeavyBlade::onEnter()
{
	super::onEnter();

	this->spellEffect->setPositionY(this->owner->getEntityBottomPointRelative().y);
	this->spellEffect->start();

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void HeavyBlade::initializePositions()
{
	super::initializePositions();
}

void HeavyBlade::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HEAVYBLADE,
			HackableCode::HackableCodeInfo(
				HeavyBlade::HeavyBladeIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_HeavyBlade::create(),
				HackableBase::HackBarColor::Yellow,
				UIResources::Menus_Icons_Shovel,
				LazyNode<HackablePreview>::create([=](){ return HeavyBladeGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zcx, Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_RegisterEcx::create()
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_CommentJmp::create()) + 
						"jmp addDamage\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_CommentSkippedCode::create()) + 
						"sub ecx, 20\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_CommentLabels::create()) + 
						"addDamage:\n" +
						"add ecx, 3\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_CommentJmp::create()) + 
						"jmp addDamage\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_CommentSkippedCode::create()) + 
						"sub rcx, 20\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Buffs_HeavyBlade_CommentLabels::create()) + 
						"addDamage:\n" +
						"add rcx, 3\n\n" +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Conditional_CommentJmp::create())
					),
				},
				true
			)
		},
	};

	this->hackables = CREATE_HACKABLES(HeavyBlade::applyHeavyBlade, codeInfoMap);

	for (HackableCode* next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void HeavyBlade::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageDealt(damageOrHealing);

	this->currentDamageDealt = damageOrHealing->damageOrHealingValue;

	this->applyHeavyBlade();

	(*damageOrHealing->damageOrHealingMin) = -std::abs(damageOrHealing->damageOrHealingValue * HeavyBlade::MinMultiplier);
	(*damageOrHealing->damageOrHealingMax) = std::abs(damageOrHealing->damageOrHealingValue * HeavyBlade::MaxMultiplier);
	(*damageOrHealing->damageOrHealing) = this->currentDamageDealt;
}

NO_OPTIMIZE void HeavyBlade::applyHeavyBlade()
{
	static volatile int currentDamageDealtLocal = 0;

	currentDamageDealtLocal = this->currentDamageDealt;

	ASM_PUSH_EFLAGS()
	ASM(push ZCX);
	ASM_MOV_REG_VAR(ecx, currentDamageDealtLocal);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HEAVYBLADE);
	ASM(jmp addDamage);
	ASM(sub ZCX, 20);
	ASM(addDamage:);
	ASM(add ZCX, 3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(currentDamageDealtLocal, ecx);

	ASM(pop ZCX);
	ASM_POP_EFLAGS()

	this->currentDamageDealt = currentDamageDealtLocal;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
