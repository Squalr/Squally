#include "RestoreHealth.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Buffs/RestoreHealth/RestoreHealthGenericPreview.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/RestorePotion/IncrementHealth/IncrementHealth.h"
#include "Strings/Hacking/Objects/RestorePotion/IncrementHealth/RegisterEdi.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RESTORE 1

const std::string RestoreHealth::RestoreHealthIdentifier = "restore-health";

RestoreHealth* RestoreHealth::create(PlatformerEntity* target, int healAmount)
{
	RestoreHealth* instance = new RestoreHealth(target, healAmount);

	instance->autorelease();

	return instance;
}

RestoreHealth::RestoreHealth(PlatformerEntity* target, int healAmount) : super(target, UIResources::EmptyImage, healAmount, 0.5f)
{
}

RestoreHealth::~RestoreHealth()
{
}

void RestoreHealth::registerHackables()
{
	super::registerHackables();

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

void RestoreHealth::tick()
{
	super::tick();
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

	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(incrementAmount, target));

	HACKABLES_STOP_SEARCH();
}
