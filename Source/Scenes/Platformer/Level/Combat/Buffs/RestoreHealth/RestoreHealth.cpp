#include "RestoreHealth.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Buffs/RestoreHealth/RestoreHealthGenericPreview.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/RestorePotion/IncrementHealth/IncrementHealth.h"
#include "Strings/Hacking/Objects/RestorePotion/IncrementHealth/RegisterEdi.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RESTORE 1

const std::string RestoreHealth::RestoreHealthIdentifier = "restore-health";
const float RestoreHealth::TimeBetweenTicks = 0.5f;

RestoreHealth* RestoreHealth::create(PlatformerEntity* caster, PlatformerEntity* target, int healAmount)
{
	RestoreHealth* instance = new RestoreHealth(caster, target, healAmount);

	instance->autorelease();

	return instance;
}

RestoreHealth::RestoreHealth(PlatformerEntity* caster, PlatformerEntity* target, int healAmount) : super(caster, target)
{
	this->healEffect = SmartAnimationSequenceNode::create(FXResources::Heal_Heal_0000);
	this->healAmount = MathUtils::clamp(healAmount, 1, 255);

	this->addChild(this->healEffect);
}

RestoreHealth::~RestoreHealth()
{
}

void RestoreHealth::onEnter()
{
	super::onEnter();

	this->healEffect->playAnimationRepeat(FXResources::Heal_Heal_0000, 0.05f);

	for (int healIndex = 0; healIndex < this->healAmount; healIndex++)
	{
		this->runAction(Sequence::create(
			DelayTime::create(RestoreHealth::TimeBetweenTicks * float(healIndex + 1)),
			CallFunc::create([=]()
			{
				this->runRestoreTick();
			}),
			nullptr
		));
	}

	this->runAction(Sequence::create(
		DelayTime::create(RestoreHealth::TimeBetweenTicks * float(this->healAmount + 1)),
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

void RestoreHealth::initializePositions()
{
	super::initializePositions();

	this->setPosition(Vec2(0.0f, 126.0f));
}

void RestoreHealth::registerHackables()
{
	super::registerHackables();

	if (this->target == nullptr)
	{
		return;
	}

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_RESTORE,
			HackableCode::LateBindData(
				RestoreHealth::RestoreHealthIdentifier,
				Strings::Hacking_Objects_RestorePotion_IncrementHealth_IncrementHealth::create(),
				UIResources::Menus_Icons_ArrowUp,
				RestoreHealthGenericPreview::create(),
				{
					{ HackableCode::Register::zdi, Strings::Hacking_Objects_RestorePotion_IncrementHealth_RegisterEdi::create() }
				},
				2.0f
			)
		},
	};

	auto restoreFunc = &RestoreHealth::runRestoreTick;
	this->hackables = HackableCode::create((void*&)restoreFunc, lateBindMap);

	for (auto it = this->hackables.begin(); it != this->hackables.end(); it++)
	{
		this->target->registerCode(*it);
	}
}

void RestoreHealth::runRestoreTick()
{
	int incrementAmount = 0;

	ASM(push EDI);
	ASM(mov EDI, 0)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RESTORE);
	ASM(inc EDI);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(incrementAmount, EDI);

	ASM(pop EDI);

	incrementAmount = MathUtils::clamp(incrementAmount, -1, 1);

	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(this->caster, this->target, incrementAmount));

	HACKABLES_STOP_SEARCH();
}
