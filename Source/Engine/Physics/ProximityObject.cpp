#include "ProximityObject.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/GetProjectileAcceleration.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/RegisterEax.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/RegisterEbx.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/RegisterEcx.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration/RegisterEsi.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/GetProjectileVelocity.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/RegisterEax.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/RegisterEbx.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/RegisterEcx.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity/RegisterEsi.h"

#define LOCAL_FUNC_ID_VELOCITY 100
#define LOCAL_FUNC_ID_ACCELERATION 101

using namespace cocos2d;

ProximityObject* ProximityObject::create(float radius)
{
	ProximityObject* instance = new ProximityObject(radius);

	instance->autorelease();

	return instance;
}

ProximityObject::ProximityObject(float radius) : HackableObject(ValueMap())
{
	this->radius = radius;
	this->velocity = Vec3::ZERO;
	this->acceleration = Vec3::ZERO;
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

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_VELOCITY,
			HackableCode::LateBindData(
				"proximity-object",
				Strings::Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_GetProjectileVelocity::create(),
				UIResources::Menus_Icons_AxeSlash,
				this->createVelocityPreview(),
				{
					{ HackableCode::Register::eax, Strings::Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_RegisterEax::create() },
					{ HackableCode::Register::ebx, Strings::Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_RegisterEbx::create() },
					{ HackableCode::Register::ecx, Strings::Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_RegisterEcx::create() },
					{ HackableCode::Register::esi, Strings::Hacking_Objects_Combat_Projectiles_GetProjectileVelocity_RegisterEsi::create() }
				}
			)
		},
		{
			LOCAL_FUNC_ID_ACCELERATION,
			HackableCode::LateBindData(
				"proximity-object",
				Strings::Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_GetProjectileAcceleration::create(),
				UIResources::Menus_Icons_Scale,
				this->createAccelerationPreview(),
				{
					{ HackableCode::Register::eax, Strings::Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_RegisterEax::create() },
					{ HackableCode::Register::ebx, Strings::Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_RegisterEbx::create() },
					{ HackableCode::Register::ecx, Strings::Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_RegisterEcx::create() },
					{ HackableCode::Register::esi, Strings::Hacking_Objects_Combat_Projectiles_GetProjectileAcceleration_RegisterEsi::create() }
				}
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

void ProximityObject::launchTowardsTarget(Node* target, Vec2 offset, float spinSpeed, float secondsPer256pxLinearDistance, Vec3 gravity)
{
	Vec3 thisPosition = GameUtils::getWorldCoords3D(this);
	Vec3 targetPosition = GameUtils::getWorldCoords3D(target) + Vec3(offset.x, offset.y, 0.0f);
	float duration = targetPosition.distance(thisPosition) / 480.0f * secondsPer256pxLinearDistance;
	bool isLeft = targetPosition.x < thisPosition.x;

	if (spinSpeed != 0.0f)
	{
		this->runAction(RotateBy::create(duration, (isLeft ? -1.0f : 1.0f) * duration * 360.0f * spinSpeed));
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

Vec3 ProximityObject::getVelocity()
{
	Vec3 velocityCopy = this->velocity;
	const volatile float* velocityPtrX = &velocityCopy.x;
	const volatile float* velocityPtrY = &velocityCopy.y;
	const volatile float* velocityPtrZ = &velocityCopy.z;
	static const volatile int* freeMemory = new int[128];

	// Push velocity variables onto FPU stack
	ASM(push EAX)
	ASM(push EBX)
	ASM(push ECX)
	ASM(push ESI)
	ASM_MOV_REG_VAR(EAX, velocityPtrX);
	ASM_MOV_REG_VAR(EBX, velocityPtrY);
	ASM_MOV_REG_VAR(ECX, velocityPtrZ);
	ASM_MOV_REG_VAR(ESI, freeMemory);
	ASM(fld dword ptr[ECX])
	ASM(fld dword ptr[EBX])
	ASM(fld dword ptr[EAX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_VELOCITY);
	ASM(fstp dword ptr[EAX])
	ASM(fstp dword ptr[EBX])
	ASM(fstp dword ptr[ECX])
	ASM_NOP15();
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(velocityPtrX, EAX);
	ASM_MOV_VAR_REG(velocityPtrY, EBX);
	ASM_MOV_VAR_REG(velocityPtrZ, ECX);

	ASM(pop ESI)
	ASM(pop ECX)
	ASM(pop EBX)
	ASM(pop EAX)

	HACKABLES_STOP_SEARCH();

	return velocityCopy;
}

Vec3 ProximityObject::getAcceleration()
{
	Vec3 accelerationCopy = this->acceleration;
	const volatile float* accelerationPtrX = &accelerationCopy.x;
	const volatile float* accelerationPtrY = &accelerationCopy.y;
	const volatile float* accelerationPtrZ = &accelerationCopy.z;
	static const volatile int* freeMemory = new int[128];

	// Push acceleration variables onto FPU stack
	ASM(push EAX)
	ASM(push EBX)
	ASM(push ECX)
	ASM(push ESI)
	ASM_MOV_REG_VAR(EAX, accelerationPtrX);
	ASM_MOV_REG_VAR(EBX, accelerationPtrY);
	ASM_MOV_REG_VAR(ECX, accelerationPtrZ);
	ASM_MOV_REG_VAR(ESI, freeMemory);
	ASM(fld dword ptr[ECX])
	ASM(fld dword ptr[EBX])
	ASM(fld dword ptr[EAX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_ACCELERATION);
	ASM(fstp dword ptr[EAX])
	ASM(fstp dword ptr[EBX])
	ASM(fstp dword ptr[ECX])
	ASM_NOP15();
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(accelerationPtrX, EAX);
	ASM_MOV_VAR_REG(accelerationPtrY, EBX);
	ASM_MOV_VAR_REG(accelerationPtrZ, ECX);

	ASM(pop ESI)
	ASM(pop ECX)
	ASM(pop EBX)
	ASM(pop EAX)

	HACKABLES_STOP_SEARCH();

	return accelerationCopy;
}

bool ProximityObject::isInProximityTo(Node* other)
{
	return other == nullptr ? false : (this->getPosition3D().distance(other->getPosition3D()) < this->radius);
}
