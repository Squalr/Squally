#include "Catapult.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/SpawnEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Physics/Catapult/CatapultBall.h"
#include "Objects/Platformer/Physics/Catapult/CatapultApplyPowerPreview.h"
#include "Objects/Platformer/Physics/Catapult/CatapultGenericPreview.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/Catapult/ApplyPower/ApplyPower.h"
#include "Strings/Hacking/Objects/Catapult/ApplyPower/RegisterEax.h"
#include "Strings/Hacking/Objects/Catapult/ApplyPower/RegisterXmm0.h"
#include "Strings/Hacking/Objects/Catapult/ApplyPower/RegisterXmm1.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_APPLY_POWER 1

const std::string Catapult::MapKeyCatapult = "catapult";
const float Catapult::InteractCooldown = 3.0f;
const float Catapult::LaunchPowerDefault = 0.90f;
const Vec2 Catapult::LaunchVelocityBase = Vec2(1200.0f, 1200.0f);

Catapult* Catapult::create(ValueMap& initProperties)
{
	Catapult* instance = new Catapult(initProperties);
	
	instance->autorelease();

	return instance;
}

Catapult::Catapult(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->catapultAnimations = SmartAnimationNode::create(ObjectResources::War_Machines_Catapult_Animations);
	this->catapultCollision = CollisionObject::create(PhysicsBody::createBox(Size(512.0f, 320.0f)), (CollisionType)PlatformerCollisionType::Physics, false, false);
	this->ballAnimationPart = this->catapultAnimations->getAnimationPart("BALL");
	this->launchPower = Catapult::LaunchPowerDefault;
	this->interactionEnabled = false;
	this->currentCooldown = 0.0f;

	float height = GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyHeight, Value(0.0f)).asFloat();
	this->catapultAnimations->setPositionY(-height / 2.0f);
	this->catapultAnimations->setScale(1.75f);

	this->catapultCollision->addChild(this->catapultAnimations);
	this->addChild(this->catapultCollision);
}

Catapult::~Catapult()
{
}

void Catapult::onEnter()
{
	super::onEnter();

	this->interactionEnabled = false;
	this->currentCooldown = 0.0f;

	this->scheduleUpdate();
}

void Catapult::initializePositions()
{
	super::initializePositions();
}

void Catapult::initializeListeners()
{
	super::initializeListeners();

	this->catapultCollision->whenCollidesWith({ (int)PlatformerCollisionType::Physics, (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Force }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->catapultCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		this->interactionEnabled = true;

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->catapultCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData collisionData)
	{
		this->interactionEnabled = false;

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Catapult::update(float dt)
{
	super::update(dt);

	if (this->currentCooldown > 0.0f)
	{
		this->currentCooldown -= dt;
	}

	if (this->interactionEnabled && this->currentCooldown <= 0.0f)
	{
		if (Input::isKeyJustPressed(EventKeyboard::KeyCode::KEY_V))
		{
			this->launchCatapult();
		}
	}
}

Vec2 Catapult::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Catapult::registerHackables()
{
	super::registerHackables();

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_APPLY_POWER,
			HackableCode::LateBindData(
				Catapult::MapKeyCatapult,
				Strings::Hacking_Objects_Catapult_ApplyPower_ApplyPower::create(),
				UIResources::Menus_Icons_Meteor,
				CatapultApplyPowerPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Hacking_Objects_Catapult_ApplyPower_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Hacking_Objects_Catapult_ApplyPower_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Hacking_Objects_Catapult_ApplyPower_RegisterXmm1::create() },
				},
				20.0f
			)
		},
	};

	auto applyLaunchFunc = &Catapult::applyLaunchPower;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)applyLaunchFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* Catapult::createDefaultPreview()
{
	return CatapultGenericPreview::create();
}


void Catapult::launchCatapult()
{
	this->currentCooldown = Catapult::InteractCooldown;
	this->catapultAnimations->playAnimation("Launch");

	this->runAction(Sequence::create(
		DelayTime::create(0.2f),
		CallFunc::create([=]()
		{
			this->launchBall();
		}),
		nullptr
	));
}

void Catapult::launchBall()
{
	CatapultBall* catapultBall = CatapultBall::create(ValueMap(), this->applyLaunchPower(Catapult::LaunchVelocityBase));

	this->ballAnimationPart->replaceWithObject(catapultBall, 0.0f, 0.0f);
	catapultBall->setScale(this->catapultAnimations->getScale());

	SpawnEvents::TriggerObjectSpawn(SpawnEvents::RequestObjectSpawnArgs(
		this->ballAnimationPart,
		catapultBall,
		SpawnEvents::SpawnMethod::Above
	));

	catapultBall->setRotation(0.0f);
}

cocos2d::Vec2 Catapult::applyLaunchPower(cocos2d::Vec2 baseSpeed)
{
	static float* freeMemoryForUser = new float[16];
	float resultSpeedY = this->launchPower;
	float* launchPowerPtr = &resultSpeedY;
	float* ySpeedPtr = &baseSpeed.y;

	// Prepare variables (initialize xmm0 with return value, xmm1 with loaded density)
	ASM(push EAX);
	ASM_MOV_REG_VAR(EAX, ySpeedPtr);
	ASM(movss xmm0, dword ptr [EAX]);
	ASM_MOV_REG_VAR(EAX, launchPowerPtr);
	ASM(movss xmm1, dword ptr [EAX]);
	ASM(pop EAX);

	ASM(push EAX);
	ASM_MOV_REG_VAR(EAX, freeMemoryForUser);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_APPLY_POWER);
	ASM(mulss xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();
	ASM(pop EAX);

	// Copy from xmm0 to the output variable
	ASM(push EAX);
	ASM_MOV_REG_VAR(EAX, launchPowerPtr);
	ASM(movss dword ptr [EAX], xmm0);
	ASM(pop EAX);

	HACKABLES_STOP_SEARCH();

	return Vec2(baseSpeed.x, MathUtils::clamp(resultSpeedY, -Catapult::LaunchVelocityBase.y, Catapult::LaunchVelocityBase.y));
}
