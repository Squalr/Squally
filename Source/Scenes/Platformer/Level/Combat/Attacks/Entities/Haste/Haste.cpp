#include "Haste.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Haste/HasteClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Haste/HasteGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_HASTE 1

const std::string Haste::HasteIdentifier = "haste";

Haste* Haste::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Haste* instance = new Haste(caster, target);

	instance->autorelease();

	return instance;
}

Haste::Haste(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, BuffData(6.0f, Haste::HasteIdentifier))
{
	this->clippy = HasteClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
}

Haste::~Haste()
{
}

void Haste::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void Haste::initializePositions()
{
	super::initializePositions();

	this->spellEffect->setPositionY(-this->target->getEntityCenterPoint().y / 2.0f);
}

void Haste::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void Haste::registerHackables()
{
	super::registerHackables();

	if (this->target == nullptr)
	{
		return;
	}

	this->clippy->setIsEnabled(false);

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HASTE,
			HackableCode::HackableCodeInfo(
				Haste::HasteIdentifier,
				Strings::Menus_Hacking_Abilities_Entities_Generic_Haste_Haste::create(),
				UIResources::Menus_Icons_Clock,
				HasteGenericPreview::create(),
				{
					{ HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Entities_Generic_Haste_RegisterEsi::create() },
					{ HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Entities_Generic_Haste_RegisterXmm3::create() }
				},
				int(HackFlags::None),
				this->buffData.duration,
				0.0f,
				this->clippy
			)
		},
	};

	auto hasteFunc = &Haste::applyHaste;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void Haste::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
	this->currentSpeed = *timelineSpeed;

	this->applyHaste();

	*timelineSpeed = this->currentSpeed;
}

NO_OPTIMIZE void Haste::applyHaste()
{
	volatile float speedBonus = 0.0f;
	volatile float increment = 0.75f;
	volatile float* speedBonusPtr = &speedBonus;
	volatile float* incrementPtr = &increment;

	ASM(push ZSI);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZSI, speedBonusPtr);
	ASM_MOV_REG_VAR(ZBX, incrementPtr);
	ASM(movss xmm3, [ZBX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(movss [ZSI], xmm3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZSI);

	this->currentSpeed += MathUtils::clamp(speedBonus, -1.0f, 1.0f);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
