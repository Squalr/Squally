#include "MayanGemBlue.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_GEM 1

MayanGemBlue* MayanGemBlue::create()
{
	MayanGemBlue* instance = new MayanGemBlue();

	instance->autorelease();

	return instance;
}

MayanGemBlue::MayanGemBlue() : super(ObjectResources::Doors_Mayan_BlueGem, ObjectResources::Doors_Mayan_BlueGemDisabled)
{
}

MayanGemBlue::~MayanGemBlue()
{
}

void MayanGemBlue::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_GEM,
			HackableCode::HackableCodeInfo(
				"mayan-gem-blue",
				nullptr, // Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_SetTargetAngle::create(),
				UIResources::Menus_Icons_CrossHair,
				nullptr, // PendulumBladeSetAnglePreview::create(),
				{
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_RegisterEbx::create() }
				},
				int(HackFlags::None),
				15.0f,
				0.0f,
				nullptr // this->pendulumBladeClippy
			)
		},
	};

	auto gemFunc = &MayanGemBlue::runGemBlue;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)gemFunc, codeInfoMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

int MayanGemBlue::runGem(int currentIndex)
{
	return this->runGemBlue(currentIndex);
}

NO_OPTIMIZE int MayanGemBlue::runGemBlue(int currentIndex)
{
	volatile int newIndex = currentIndex;

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZBX, newIndex);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GEM);
	ASM(add ZBX, 7);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(newIndex, ZBX);

	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(newIndex, 0, 11);
}
END_NO_OPTIMIZE