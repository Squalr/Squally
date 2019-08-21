#include "ProximityObject.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/GetProjectileAcceleration.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/RegisterEax.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/RegisterEbx.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/RegisterEcx.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/RegisterEsi.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/GetProjectileVelocity.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/RegisterEax.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/RegisterEbx.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/RegisterEcx.h"
#include "Strings/Menus/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/RegisterEsi.h"

#define LOCAL_FUNC_ID_VELOCITY 100
#define LOCAL_FUNC_ID_ACCELERATION 101

using namespace cocos2d;

ProximityObject* ProximityObject::create(float radius, bool allowHacking)
{
	ProximityObject* instance = new ProximityObject(radius, allowHacking);

	instance->autorelease();

	return instance;
}

ProximityObject::ProximityObject(float radius, bool allowHacking) : HackableObject(ValueMap())
{
	this->radius = radius;
	this->velocity = Vec3::ZERO;
	this->acceleration = Vec3::ZERO;
	this->allowHacking = allowHacking;

	this->contentNode = Node::create();

	this->addChild(this->contentNode);
}

ProximityObject::~ProximityObject()
{
}

void ProximityObject::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void ProximityObject::initializePositions()
{
	super::initializePositions();
}

void ProximityObject::update(float dt)
{
	super::update(dt);

	this->setVelocity(this->velocity + this->getAcceleration() * dt);
	this->setPosition3D(this->getPosition3D() + this->getVelocity() * dt);
}

void ProximityObject::registerHackables()
{
	super::registerHackables();

	if (!this->allowHacking)
	{
		return;
	}

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_VELOCITY,
			HackableCode::LateBindData(
				"proximity-object",
				Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_GetProjectileVelocity::create(),
				UIResources::Menus_Icons_AxeSlash,
				this->createVelocityPreview(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_RegisterEbx::create() },
					{ HackableCode::Register::zcx, Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_RegisterEcx::create() },
					{ HackableCode::Register::zsi, Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_RegisterEsi::create() }
				},
				10,
				3.0f
			)
		},
		{
			LOCAL_FUNC_ID_ACCELERATION,
			HackableCode::LateBindData(
				"proximity-object",
				Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_GetProjectileAcceleration::create(),
				UIResources::Menus_Icons_Scale,
				this->createAccelerationPreview(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_RegisterEbx::create() },
					{ HackableCode::Register::zcx, Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_RegisterEcx::create() },
					{ HackableCode::Register::zsi, Strings::Menus_Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_RegisterEsi::create() }
				},
				10,
				3.0f
			)
		},
	};

	auto velocityFunc = &ProximityObject::getVelocity;
	std::vector<HackableCode*> velocityHackables = HackableCode::create((void*&)velocityFunc, lateBindMap);

	for (auto it = velocityHackables.begin(); it != velocityHackables.end(); it++)
	{
		this->registerCode(*it);
	}

	auto accelerationFunc = &ProximityObject::getAcceleration;
	std::vector<HackableCode*> accelerationHackables = HackableCode::create((void*&)accelerationFunc, lateBindMap);

	for (auto it = accelerationHackables.begin(); it != accelerationHackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* ProximityObject::createDefaultPreview()
{
	return nullptr;
}

HackablePreview* ProximityObject::createVelocityPreview()
{
	return nullptr;
}

HackablePreview* ProximityObject::createAccelerationPreview()
{
	return nullptr;
}

void ProximityObject::launchTowardsTarget(Node* target, Vec2 offset, float spinSpeed, Vec3 secondsPer256pxLinearDistance, Vec3 gravity)
{
	Vec3 thisPosition = GameUtils::getWorldCoords3D(this);
	Vec3 targetPosition = GameUtils::getWorldCoords3D(target) + Vec3(offset.x, offset.y, 0.0f);
	Vec3 duration = secondsPer256pxLinearDistance * (targetPosition.distance(thisPosition) / 256.0f);
	float maxDuration = std::max(std::max(duration.x, duration.y), duration.z);
	bool isLeft = targetPosition.x < thisPosition.x;

	if (spinSpeed != 0.0f)
	{
		this->contentNode->runAction(RotateBy::create(maxDuration, (isLeft ? -1.0f : 1.0f) * maxDuration * 360.0f * spinSpeed));
	}

	this->setAcceleration(gravity);
	this->setVelocity(AlgoUtils::computeArcVelocity(thisPosition, targetPosition, gravity, duration));
}

void ProximityObject::setVelocity(cocos2d::Vec3 velocity)
{
	this->velocity = velocity;
}

void ProximityObject::setAcceleration(cocos2d::Vec3 acceleration)
{
	this->acceleration = acceleration;
}

NO_OPTIMIZE Vec3 ProximityObject::getVelocity()
{
	Vec3 velocityCopy = this->velocity;
	static const volatile int* freeMemory = new int[128];
	const volatile float* velocityPtrX = &velocityCopy.x;
	const volatile float* velocityPtrY = &velocityCopy.y;
	const volatile float* velocityPtrZ = &velocityCopy.z;

	// Push velocity variables onto FPU stack
	ASM(push ZAX)
	ASM(push ZBX)
	ASM(push ZCX)
	ASM(push ZSI)
	ASM_MOV_REG_VAR(ZAX, velocityPtrX);
	ASM_MOV_REG_VAR(ZBX, velocityPtrY);
	ASM_MOV_REG_VAR(ZCX, velocityPtrZ);
	ASM_MOV_REG_VAR(ZSI, freeMemory);
	ASM(fld dword ptr[ZCX])
	ASM(fld dword ptr[ZBX])
	ASM(fld dword ptr[ZAX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_VELOCITY);
	ASM(fstp dword ptr[ZAX])
	ASM(fstp dword ptr[ZBX])
	ASM(fstp dword ptr[ZCX])
	ASM_NOP15();
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(velocityPtrX, ZAX);
	ASM_MOV_VAR_REG(velocityPtrY, ZBX);
	ASM_MOV_VAR_REG(velocityPtrZ, ZCX);

	ASM(pop ZSI)
	ASM(pop ZCX)
	ASM(pop ZBX)
	ASM(pop ZAX)

	HACKABLES_STOP_SEARCH();

	return velocityCopy;
}

NO_OPTIMIZE Vec3 ProximityObject::getAcceleration()
{
	Vec3 accelerationCopy = this->acceleration;
	const volatile float* accelerationPtrX = &accelerationCopy.x;
	const volatile float* accelerationPtrY = &accelerationCopy.y;
	const volatile float* accelerationPtrZ = &accelerationCopy.z;
	static const volatile int* freeMemory = new int[128];

	// Push acceleration variables onto FPU stack
	ASM(push ZAX)
	ASM(push ZBX)
	ASM(push ZCX)
	ASM(push ZSI)
	ASM_MOV_REG_VAR(ZAX, accelerationPtrX);
	ASM_MOV_REG_VAR(ZBX, accelerationPtrY);
	ASM_MOV_REG_VAR(ZCX, accelerationPtrZ);
	ASM_MOV_REG_VAR(ZSI, freeMemory);
	ASM(fld dword ptr[ZCX])
	ASM(fld dword ptr[ZBX])
	ASM(fld dword ptr[ZAX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_ACCELERATION);
	ASM(fstp dword ptr[ZAX])
	ASM(fstp dword ptr[ZBX])
	ASM(fstp dword ptr[ZCX])
	ASM_NOP15();
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(accelerationPtrX, ZAX);
	ASM_MOV_VAR_REG(accelerationPtrY, ZBX);
	ASM_MOV_VAR_REG(accelerationPtrZ, ZCX);

	ASM(pop ZSI)
	ASM(pop ZCX)
	ASM(pop ZBX)
	ASM(pop ZAX)

	HACKABLES_STOP_SEARCH();

	return accelerationCopy;
}

bool ProximityObject::isInProximityTo(Node* other)
{
	return other == nullptr ? false : (this->getPosition3D().distance(other->getPosition3D()) < this->radius);
}
