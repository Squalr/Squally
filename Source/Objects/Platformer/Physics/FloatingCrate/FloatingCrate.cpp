#include "FloatingCrate.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Objects/Platformer/Physics/FloatingCrate/FloatingCrateGenericPreview.h"
#include "Objects/Platformer/Physics/FloatingCrate/FloatingCrateGetDensityPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_GET_DENSITY 1

const std::string FloatingCrate::MapKeyFloatingCrate = "floating-crate";

FloatingCrate* FloatingCrate::create(ValueMap& properties)
{
	FloatingCrate* instance = new FloatingCrate(properties);
	
	instance->autorelease();

	return instance;
}

FloatingCrate::FloatingCrate(ValueMap& properties) : super(properties)
{
	this->sprite = Sprite::create(ObjectResources::Physics_WoodenCrate_WoodenCrate);
	this->collision = CollisionObject::create(PhysicsBody::createBox(Size(160.0f, 160.0f)), (CollisionType)PlatformerCollisionType::Physics, false, true);

	this->collision->whenCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->collision->addChild(this->sprite);
	this->contentNode->addChild(this->collision);
}

FloatingCrate::~FloatingCrate()
{
}

void FloatingCrate::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void FloatingCrate::initializePositions()
{
	super::initializePositions();
}

void FloatingCrate::update(float dt)
{
	super::update(dt);
}

Vec2 FloatingCrate::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void FloatingCrate::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_GET_DENSITY,
			HackableCode::HackableCodeInfo(
				FloatingCrate::MapKeyFloatingCrate,
				Strings::Menus_Hacking_Objects_FloatingObjects_GetDensity_GetDensity::create(),
				UIResources::Menus_Icons_Anvil,
				FloatingCrateGetDensityPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_FloatingObjects_GetDensity_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Objects_FloatingObjects_GetDensity_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Objects_FloatingObjects_GetDensity_RegisterXmm1::create() },
				},
				int(HackFlags::None),
				8.0f
			)
		},
	};

	auto densityFunc = &FloatingCrate::getDensityNonVirtual;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)densityFunc, codeInfoMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* FloatingCrate::createDefaultPreview()
{
	return FloatingCrateGenericPreview::create();
}

float FloatingCrate::getDensity()
{
	return this->getDensityNonVirtual();
}

NO_OPTIMIZE float FloatingCrate::getDensityNonVirtual()
{
	volatile static float* freeMemoryForUser = new float[16];
	volatile float densityRet = 0.5f;
	volatile float* densityRetPtr = &densityRet;
	volatile float densityCopy = this->loadedDensity;
	volatile float* densityCopyPtr = &densityCopy;

	// Prepare variables (initialize xmm0 with return value, xmm1 with loaded density)
	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, densityRetPtr);
	ASM(movss xmm0, dword ptr [ZAX]);
	ASM_MOV_REG_VAR(ZAX, densityCopyPtr);
	ASM(movss xmm1, dword ptr [ZAX]);
	ASM(pop ZAX);

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, freeMemoryForUser);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GET_DENSITY);
	ASM(movss xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();
	ASM(pop ZAX);

	// Copy from xmm0 to the output variable
	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, densityRetPtr);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM(pop ZAX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(densityRet, 0.0f, 1.0f);
}
END_NO_OPTIMIZE

float FloatingCrate::getObjectHeight()
{
	return this->sprite == nullptr ? 0.0f : this->sprite->getContentSize().height;
}
