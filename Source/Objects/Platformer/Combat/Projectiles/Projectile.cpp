#include "Projectile.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_VELOCITY 100
#define LOCAL_FUNC_ID_ACCELERATION 101

Projectile::Projectile(PlatformerEntity* caster, cocos2d::PhysicsBody* hitBox, CombatCollisionType combatCollisionType, bool allowHacking) : super(ValueMap())
{
	this->caster = caster;
	this->allowHacking = allowHacking;
	this->noCollideDuration = 1.0f;
	this->launchVelocity = Vec3::ZERO;
	this->launchAcceleration = Vec3::ZERO;
	this->spinSpeed = 0.0f;
	this->contentNode = Node::create();
	this->collisionObject = CollisionObject::create(ValueMap(),
		hitBox,
		(int)combatCollisionType,
		false,
		false
	);

	this->collisionObject->setPhysicsEnabled(false);

	this->addChild(this->contentNode);
	this->addChild(this->collisionObject);
}

Projectile::~Projectile()
{
}

void Projectile::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Projectile::initializePositions()
{
	super::initializePositions();
}

void Projectile::initializeListeners()
{
	super::initializeListeners();
}

void Projectile::update(float dt)
{
	super::update(dt);

	if (this->noCollideDuration > 0.0f)
	{
		this->noCollideDuration -= dt;

		if (this->noCollideDuration <= 0.0f)
		{
			this->collisionObject->setPhysicsEnabled(true);
		}
	}

	if (this->spinSpeed != 0.0f)
	{
		this->setRotation(this->getRotation() + this->spinSpeed * dt);
	}

	this->setLaunchVelocity(this->launchVelocity + this->getLaunchAcceleration() * dt);
	this->setPosition3D(this->getPosition3D() + this->getLaunchVelocity() * dt);
}

void Projectile::registerHackables()
{
	super::registerHackables();

	if (!this->allowHacking)
	{
		return;
	}

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_VELOCITY,
			HackableCode::HackableCodeInfo(
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
				int(HackFlags::Gravity),
				3.0f
			)
		},
		{
			LOCAL_FUNC_ID_ACCELERATION,
			HackableCode::HackableCodeInfo(
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
				int(HackFlags::Gravity),
				3.0f
			)
		},
	};

	auto velocityFunc = &Projectile::getLaunchVelocity;
	std::vector<HackableCode*> velocityHackables = HackableCode::create((void*&)velocityFunc, codeInfoMap);

	for (auto it = velocityHackables.begin(); it != velocityHackables.end(); it++)
	{
		this->registerCode(*it);
	}

	auto accelerationFunc = &Projectile::getLaunchAcceleration;
	std::vector<HackableCode*> accelerationHackables = HackableCode::create((void*&)accelerationFunc, codeInfoMap);

	for (auto it = accelerationHackables.begin(); it != accelerationHackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* Projectile::createDefaultPreview()
{
	return nullptr;
}

HackablePreview* Projectile::createVelocityPreview()
{
	return nullptr;
}

HackablePreview* Projectile::createAccelerationPreview()
{
	return nullptr;
}

void Projectile::launchTowardsTarget(Node* target, Vec2 offset, float spinSpeed, Vec3 secondsPer256pxLinearDistance, Vec3 gravity)
{
	Vec3 thisPosition = GameUtils::getWorldCoords3D(this);
	Vec3 targetPosition = GameUtils::getWorldCoords3D(target) + Vec3(offset.x, offset.y, 0.0f);
	Vec3 duration = secondsPer256pxLinearDistance * (targetPosition.distance(thisPosition) / 256.0f);
	bool isLeft = targetPosition.x < thisPosition.x;
	
	// Disable collision for the first 256px of travel distance
	float maxSpeed = std::max(0.1f, std::max(std::max(secondsPer256pxLinearDistance.x, secondsPer256pxLinearDistance.y), secondsPer256pxLinearDistance.z));
	this->noCollideDuration = maxSpeed;
	this->collisionObject->setPhysicsEnabled(false);

	this->spinSpeed = (isLeft ? -1.0f : 1.0f) * 360.0f * spinSpeed;

	this->setLaunchAcceleration(gravity);
	this->setLaunchVelocity(AlgoUtils::computeArcVelocity(thisPosition, targetPosition, gravity, duration));
}

void Projectile::setLaunchVelocity(cocos2d::Vec3 velocity)
{
	this->launchVelocity = velocity;
}

void Projectile::setLaunchAcceleration(cocos2d::Vec3 acceleration)
{
	this->launchAcceleration = acceleration;
}

CollisionObject* Projectile::getCollision()
{
	return this->collisionObject;
}

NO_OPTIMIZE Vec3 Projectile::getLaunchVelocity()
{
	Vec3 velocityCopy = this->launchVelocity;
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
END_NO_OPTIMIZE

NO_OPTIMIZE Vec3 Projectile::getLaunchAcceleration()
{
	Vec3 accelerationCopy = this->launchAcceleration;
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
END_NO_OPTIMIZE
