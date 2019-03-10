#include "FloatingAsteroid.h"

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

#include "Objects/Platformer/Physics/FloatingAsteroid/FloatingAsteroidGenericPreview.h"
#include "Objects/Platformer/Physics/FloatingAsteroid/FloatingAsteroidGetDensityPreview.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/FloatingObjects/GetDensity/GetDensity.h"
#include "Strings/Hacking/Objects/FloatingObjects/GetDensity/RegisterEax.h"
#include "Strings/Hacking/Objects/FloatingObjects/GetDensity/RegisterXmm0.h"
#include "Strings/Hacking/Objects/FloatingObjects/GetDensity/RegisterXmm1.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_GET_DENSITY 1

const std::string FloatingAsteroid::MapKeyFloatingAsteroid = "floating-asteroid";

FloatingAsteroid* FloatingAsteroid::create(ValueMap& initProperties)
{
	FloatingAsteroid* instance = new FloatingAsteroid(initProperties);
	
	instance->autorelease();

	return instance;
}

FloatingAsteroid::FloatingAsteroid(ValueMap& initProperties) : super(initProperties)
{
	this->sprite = Sprite::create(ObjectResources::Physics_Asteroid_Asteroid);
	this->collision = CollisionObject::create(PhysicsBody::createCircle(96.0f), (CollisionType)PlatformerCollisionType::Physics, false, true);

	this->collision->whenCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->collision->addChild(this->sprite);
	this->contentNode->addChild(this->collision);
}

FloatingAsteroid::~FloatingAsteroid()
{
}

void FloatingAsteroid::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void FloatingAsteroid::initializePositions()
{
	super::initializePositions();
}

void FloatingAsteroid::update(float dt)
{
	super::update(dt);
}

Vec2 FloatingAsteroid::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void FloatingAsteroid::registerHackables()
{
	super::registerHackables();

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_GET_DENSITY,
			HackableCode::LateBindData(
				FloatingAsteroid::MapKeyFloatingAsteroid,
				Strings::Hacking_Objects_FloatingObjects_GetDensity_GetDensity::create(),
				UIResources::Menus_Icons_Anvil,
				FloatingAsteroidGetDensityPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Hacking_Objects_FloatingObjects_GetDensity_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Hacking_Objects_FloatingObjects_GetDensity_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Hacking_Objects_FloatingObjects_GetDensity_RegisterXmm1::create() },
				},
				20.0f
			)
		},
	};

	auto densityFunc = &FloatingAsteroid::getDensityNonVirtual;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)densityFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* FloatingAsteroid::createDefaultPreview()
{
	return FloatingAsteroidGenericPreview::create();
}

float FloatingAsteroid::getDensity()
{
	return this->getDensityNonVirtual();
}

float FloatingAsteroid::getDensityNonVirtual()
{
	volatile static float* freeMemoryForUser = new float[16];
	volatile float densityRet = 0.5f;
	volatile float* densityRetPtr = &densityRet;
	volatile float densityCopy = this->loadedDensity;
	volatile float* densityCopyPtr = &densityCopy;

	// Prepare variables (initialize xmm0 with return value, xmm1 with loaded density)
	ASM(push EAX);
	ASM_MOV_REG_VAR(EAX, densityRetPtr);
	ASM(movss xmm0, dword ptr [EAX]);
	ASM_MOV_REG_VAR(EAX, densityCopyPtr);
	ASM(movss xmm1, dword ptr [EAX]);
	ASM(pop EAX);

	ASM(push EAX);
	ASM_MOV_REG_VAR(EAX, freeMemoryForUser);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GET_DENSITY);
	ASM(movss xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();
	ASM(pop EAX);

	// Copy from xmm0 to the output variable
	ASM(push EAX);
	ASM_MOV_REG_VAR(EAX, densityRetPtr);
	ASM(movss dword ptr [EAX], xmm0);
	ASM(pop EAX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(densityRet, 0.0f, 1.0f);
}

float FloatingAsteroid::getObjectHeight()
{
	return this->sprite == nullptr ? 0.0f : this->sprite->getContentSize().height;
}
