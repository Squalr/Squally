#include "RisingLava.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Liquids/Lava.h"
#include "Objects/Platformer/Liquids/RisingLavaGenericPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_RAISE 1

const std::string RisingLava::MapKey = "rising-lava";
const std::string RisingLava::HackIdentifierRisingLava = "rising-lava";

const float RisingLava::Speed = 450.0f;

RisingLava* RisingLava::create(ValueMap& properties)
{
	RisingLava* instance = new RisingLava(properties);

	instance->autorelease();

	return instance;
}

RisingLava::RisingLava(ValueMap& properties) : super(properties)
{
	this->lavaSize = CSize(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
	);

	ValueMap propertiesClone = properties;

	// Modify properties in such a way as to retain the lava position as seen in the map file
	propertiesClone[GameObject::MapKeyXPosition] = Value(-lavaSize.width / 2.0f);
	propertiesClone[GameObject::MapKeyYPosition] = Value(-lavaSize.height / 2.0f);

	this->lava = Lava::create(propertiesClone);

	this->addChild(this->lava);
}

RisingLava::~RisingLava()
{
}

void RisingLava::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void RisingLava::initializePositions()
{
	super::initializePositions();
}

void RisingLava::update(float dt)
{
	super::update(dt);
	
	if (this->isActive)
	{
		this->raiseLava(dt);
		this->repositionHackButtons();
	}
}

void RisingLava::activate()
{
	this->isActive = true;
}

Vec2 RisingLava::getButtonOffset()
{
	return Vec2(0.0f, this->lavaSize.height / 2.0f + this->lava->getPositionY());
}

void RisingLava::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_RAISE,
			HackableCode::HackableCodeInfo(
				RisingLava::HackIdentifierRisingLava,
				Strings::Menus_Hacking_Objects_RisingLava_RisingLava::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_Fire,
				LazyNode<HackablePreview>::create([=](){ return RisingLavaGenericPreview::create(); }),
				{
					{
						HackableCode::Register::zdx, Strings::Menus_Hacking_Objects_RisingLava_RegisterEdx::create(), HackableDataType::Int32, true
					},
				},
				int(HackFlags::Fire),
				3.0f,
				0.0f
			)
		},
	};

	auto func = &RisingLava::raiseLava;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* RisingLava::createDefaultPreview()
{
	return RisingLavaGenericPreview::create();
}

NO_OPTIMIZE void RisingLava::raiseLava(float dt)
{
	static volatile float PositionY = 0.0f;
	static volatile float* PositionYPtr = nullptr;
	static volatile float SpeedY = 0.0f;
	static volatile float* SpeedYPtr = nullptr;

	PositionY = this->lava->getPositionY();
	PositionYPtr = &PositionY;
	SpeedY = RisingLava::Speed * dt;
	SpeedYPtr = &SpeedY;

	ASM(push ZSI);
	ASM(push ZDX);

	ASM_MOV_REG_VAR(ZSI, PositionYPtr);
	ASM_MOV_REG_VAR(ZDX, SpeedYPtr);

	ASM(fld dword ptr [ZSI]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_RAISE);
	ASM(fadd dword ptr [ZDX]);
	ASM_NOP2();
	HACKABLE_CODE_END();

	ASM(fstp dword ptr [ZSI]);

	ASM(pop ZDX);
	ASM(pop ZSI);

	this->lava->setPositionY(PositionY);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
