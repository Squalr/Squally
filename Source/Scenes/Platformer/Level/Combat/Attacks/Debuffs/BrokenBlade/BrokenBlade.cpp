#include "BrokenBlade.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/BrokenBlade/BrokenBladeGenericPreview.h"
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

#define LOCAL_FUNC_ID_FORTITUDE 1

const std::string BrokenBlade::BrokenBladeIdentifier = "fortitude";
const std::string BrokenBlade::HackIdentifierBrokenBlade = "fortitude";

const int BrokenBlade::MaxMultiplier = 4;
const int BrokenBlade::DamageReduction = 3; // Keep in sync with asm
const float BrokenBlade::Duration = 12.0f;

BrokenBlade* BrokenBlade::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	BrokenBlade* instance = new BrokenBlade(caster, target);

	instance->autorelease();

	return instance;
}

BrokenBlade::BrokenBlade(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, UIResources::Menus_Icons_SwordBrokenAlt, BuffData(BrokenBlade::Duration, BrokenBlade::BrokenBladeIdentifier))
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	this->bubble = Sprite::create(FXResources::Auras_DefendAura);
	this->spellAura = Sprite::create(FXResources::Auras_ChantAura2);
	this->currentDamageDelt = 0;

	this->bubble->setOpacity(0);
	this->spellAura->setColor(Color3B::YELLOW);
	this->spellAura->setOpacity(0);

	this->addChild(this->spellEffect);
	this->addChild(this->bubble);
	this->addChild(this->spellAura);
}

BrokenBlade::~BrokenBlade()
{
}

void BrokenBlade::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	this->bubble->runAction(FadeTo::create(0.25f, 255));

	this->spellAura->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(0.5f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	CombatEvents::TriggerHackableCombatCue();
}

void BrokenBlade::initializePositions()
{
	super::initializePositions();
}

void BrokenBlade::registerHackables()
{
	super::registerHackables();

	if (this->owner == nullptr)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FORTITUDE,
			HackableCode::HackableCodeInfo(
				BrokenBlade::HackIdentifierBrokenBlade,
				Strings::Menus_Hacking_Abilities_Debuffs_BrokenBlade_BrokenBlade::create(),
				HackableBase::HackBarColor::Gray,
				UIResources::Menus_Icons_SwordBrokenAlt,
				BrokenBladeGenericPreview::create(),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Debuffs_BrokenBlade_RegisterEax::create(),
					},
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Debuffs_BrokenBlade_RegisterEbx::create(),
					},
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f
			)
		},
	};

	auto func = &BrokenBlade::applyBrokenBlade;
	this->hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->owner->registerCode(next);
	}
}

void BrokenBlade::onBeforeDamageDelt(ModifyableDamageOrHealing damageOrHealing)
{
	super::onBeforeDamageDelt(damageOrHealing);

	this->currentDamageDelt = damageOrHealing.originalDamageOrHealing;

	this->applyBrokenBlade();

	// Bound multiplier in either direction
	this->currentDamageDelt = MathUtils::clamp(this->currentDamageDelt, -std::abs(damageOrHealing.originalDamageOrHealing * BrokenBlade::MaxMultiplier), std::abs(damageOrHealing.originalDamageOrHealing * BrokenBlade::MaxMultiplier));
	
	*damageOrHealing.damageOrHealing = this->currentDamageDelt;
}

NO_OPTIMIZE void BrokenBlade::applyBrokenBlade()
{
	static volatile int damageDelt;

	damageDelt = this->currentDamageDelt;

	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(ZAX, damageDelt);
	ASM_MOV_REG_VAR(ZBX, 3);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FORTITUDE);
	ASM(cmp ZAX, ZBX);
	ASM(cmovge ZAX, ZBX);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageDelt, ZBX);

	ASM(pop ZBX);
	ASM(pop ZAX);

	this->currentDamageDelt = damageDelt;

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
