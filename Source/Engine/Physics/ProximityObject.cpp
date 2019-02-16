#include "ProximityObject.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileAcceleration.h"
#include "Strings/Hacking/Objects/Combat/Projectiles/GetProjectileVelocity.h"

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

	this->setVelocity(this->getVelocity() + this->acceleration * dt);
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
				Strings::Hacking_Objects_Combat_Projectiles_GetProjectileVelocity::create(),
				UIResources::Menus_Icons_AxeSlash,
				nullptr,
				{
					{ HackableCode::Register::eax, nullptr },
					{ HackableCode::Register::ebx, nullptr },
					{ HackableCode::Register::ecx, nullptr }
				}
			)
		},
	};

	auto velocityFunc = &ProximityObject::getVelocity;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)velocityFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
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
	const volatile float* velocityPtrX = &this->velocity.x;
	const volatile float* velocityPtrY = &this->velocity.y;
	const volatile float* velocityPtrZ = &this->velocity.z;

	// Push velocity variables onto FPU stack
	ASM(push EAX)
	ASM(push EBX)
	ASM(push ECX)
	ASM_MOV_REG_VAR(EAX, velocityPtrX);
	ASM_MOV_REG_VAR(EBX, velocityPtrY);
	ASM_MOV_REG_VAR(ECX, velocityPtrZ);
	ASM(fld dword ptr[EAX])
	ASM(fld dword ptr[EBX])
	ASM(fld dword ptr[ECX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_VELOCITY);
	ASM(fstp dword ptr[EAX])
	ASM(fstp dword ptr[EBX])
	ASM(fstp dword ptr[ECX])
	ASM_NOP15();
	HACKABLE_CODE_END();
	ASM_MOV_VAR_REG(velocityPtrX, EAX);
	ASM_MOV_VAR_REG(velocityPtrY, EBX);
	ASM_MOV_VAR_REG(velocityPtrZ, ECX);

	ASM(pop EAX)
	ASM(pop EBX)
	ASM(pop ECX)

	HACKABLES_STOP_SEARCH();

	return this->velocity;
}

Vec3 ProximityObject::getAcceleration()
{
	return this->acceleration;
}

bool ProximityObject::isInProximityTo(Node* other)
{
	return other == nullptr ? false : (this->getPosition3D().distance(other->getPosition3D()) < this->radius);
}
