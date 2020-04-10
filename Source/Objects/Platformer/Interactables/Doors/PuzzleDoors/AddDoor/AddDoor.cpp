#include "AddDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/AddDoor/AddDoorClippy.h"
#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/AddDoor/AddDoorPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RUN_OPERATION 1

const std::string AddDoor::MapKey = "add-door";

AddDoor* AddDoor::create(ValueMap& properties)
{
	AddDoor* instance = new AddDoor(properties);

	instance->autorelease();

	return instance;
}

AddDoor::AddDoor(ValueMap& properties) : super(properties)
{
	this->clippy = AddDoorClippy::create();

	this->registerClippy(this->clippy);
}

AddDoor::~AddDoor()
{
}

void AddDoor::onEnter()
{
	super::onEnter();

	this->enableAllClippy();

	if (this->getIsUnlocked())
	{
		this->toggleHackable(false);
	}
}

void AddDoor::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RUN_OPERATION,
			HackableCode::HackableCodeInfo(
				AddDoor::MapKey,
				Strings::Menus_Hacking_Objects_PuzzleDoor_Addition_Addition::create(),
				UIResources::Menus_Icons_Heal,
				AddDoorPreview::create(),
				{
					{ HackableCode::Register::zcx, Strings::Menus_Hacking_Objects_PuzzleDoor_Addition_RegisterEcx::create() },
				},
				int(HackFlags::None),
				14.0f,
				0.0f,
				this->clippy
			)
		},
	};

	auto incrementAnimationFunc = &AddDoor::AddDoorTransform;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)incrementAnimationFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

void AddDoor::runOperation(int puzzleIndex)
{
	this->setRealValue(puzzleIndex + 3);

	this->AddDoorTransform(puzzleIndex);
}

NO_OPTIMIZE void AddDoor::AddDoorTransform(int puzzleIndex)
{
	int transform = puzzleIndex;

	ASM(push ZCX)
	ASM_MOV_REG_VAR(ZCX, transform);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RUN_OPERATION);
	ASM(add ZCX, 2)
	ASM_NOP6();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(transform, ZCX);
	ASM(pop ZCX);

	this->setHackValue(transform);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
