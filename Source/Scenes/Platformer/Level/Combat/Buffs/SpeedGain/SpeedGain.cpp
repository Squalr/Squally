#include "SpeedGain.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Combat/Buffs/SpeedGain/SpeedGainClippy.h"
#include "Scenes/Platformer/Level/Combat/Buffs/SpeedGain/SpeedGainGenericPreview.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/RestorePotion/IncrementHealth/IncrementHealth.h"
#include "Strings/Hacking/Objects/RestorePotion/IncrementHealth/RegisterEdi.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RESTORE 1

const std::string SpeedGain::MapKeyPropertyRestorePotionTutorial = "restore-potion-tutorial";
const std::string SpeedGain::EventShowRestorePotionTutorial = "EVENT_SHOW_RESTORE_POTION_TUTORIAL";
const std::string SpeedGain::SpeedGainIdentifier = "restore-health";
const float SpeedGain::TimeBetweenTicks = 0.5f;

SpeedGain* SpeedGain::create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount)
{
	SpeedGain* instance = new SpeedGain(caster, target, healAmount);

	instance->autorelease();

	return instance;
}

SpeedGain::SpeedGain(PlatformerEntity* caster, PlatformerEntity* target, int healAmount) : super(caster, target)
{
	this->healEffect = SmartAnimationSequenceNode::create(FXResources::Heal_Heal_0000);
	this->healAmount = MathUtils::clamp(healAmount, 1, 255);
	this->impactSound = Sound::create(SoundResources::Platformer_Attacks_Spells_Heal2);
	this->healSound = Sound::create(SoundResources::Platformer_Attacks_Spells_Ding1);

	this->addChild(this->healEffect);
	this->addChild(this->impactSound);
	this->addChild(this->healSound);
}

SpeedGain::~SpeedGain()
{
}

void SpeedGain::onEnter()
{
	super::onEnter();
	
	std::vector<std::string> mapArgs = std::vector<std::string>();

	PlatformerEvents::TriggerQueryMapArgs(PlatformerEvents::QueryMapArgsArgs(&mapArgs));

	bool showClippy = (std::find(mapArgs.begin(), mapArgs.end(), SpeedGain::MapKeyPropertyRestorePotionTutorial) != mapArgs.end());

	this->runSpeedGain();

	if (showClippy)
	{
		ObjectEvents::TriggerBroadCastMapObjectState(SpeedGain::EventShowRestorePotionTutorial, ValueMap());
	}
}

void SpeedGain::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 118.0f));
}

void SpeedGain::registerHackables()
{
	super::registerHackables();

	if (this->target == nullptr)
	{
		return;
	}
	
	std::vector<std::string> mapArgs = std::vector<std::string>();

	PlatformerEvents::TriggerQueryMapArgs(PlatformerEvents::QueryMapArgsArgs(&mapArgs));

	bool showClippy = (std::find(mapArgs.begin(), mapArgs.end(), SpeedGain::MapKeyPropertyRestorePotionTutorial) != mapArgs.end());

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_RESTORE,
			HackableCode::LateBindData(
				SpeedGain::SpeedGainIdentifier,
				Strings::Hacking_Objects_RestorePotion_IncrementHealth_IncrementHealth::create(),
				UIResources::Menus_Icons_ArrowUp,
				SpeedGainGenericPreview::create(),
				{
					{ HackableCode::Register::zdi, Strings::Hacking_Objects_RestorePotion_IncrementHealth_RegisterEdi::create() }
				},
				1,
				2.0f,
				showClippy ? SpeedGainClippy::create() : nullptr
			)
		},
	};

	auto restoreFunc = &SpeedGain::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, lateBindMap);

	for (auto it = this->hackables.begin(); it != this->hackables.end(); it++)
	{
		this->target->registerCode(*it);
	}
}

void SpeedGain::runSpeedGain()
{
	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f);
	this->impactSound->play();

	const float StartDelay = 1.0f;

	for (int healIndex = 0; healIndex < this->healAmount; healIndex++)
	{
		this->runAction(Sequence::create(
			DelayTime::create(SpeedGain::TimeBetweenTicks * float(healIndex) + StartDelay),
			CallFunc::create([=]()
			{
				this->runRestoreTick();
			}),
			nullptr
		));
	}

	this->runAction(Sequence::create(
		DelayTime::create(SpeedGain::TimeBetweenTicks * float(this->healAmount) + StartDelay),
		CallFunc::create([=]()
		{
			this->healEffect->runAction(FadeTo::create(0.25f, 0));
		}),
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->removeBuff();
		}),
		nullptr
	));
}

NO_OPTIMIZE void SpeedGain::runRestoreTick()
{
	int incrementAmount = 0;

	ASM(push ZDI);
	ASM(mov ZDI, 0)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(inc ZDI);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(incrementAmount, ZDI);

	ASM(pop ZDI);

	incrementAmount = MathUtils::clamp(incrementAmount, -1, 1);

	this->healSound->play();
	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->target, incrementAmount));

	HACKABLES_STOP_SEARCH();
}
