#include "DartGun.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Traps/DartTraps/Dart.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Hacking/Objects/PendulumBlade/SetTargetAngle/SetTargetAngle.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string DartGun::MapKeyDartGun = "dart-gun";
const std::string DartGun::PivotBone = "pivot_bone";

DartGun* DartGun::create(ValueMap& properties)
{
	DartGun* instance = new DartGun(properties);

	instance->autorelease();

	return instance;
}

DartGun::DartGun(ValueMap& properties) : super(properties)
{
	this->dartNode = Node::create();
	this->dartGunAnimations = SmartAnimationNode::create(ObjectResources::War_Machines_Dartgun_Animations);
	this->timeSinceLastShot = 0.0f;
	this->cannon = this->dartGunAnimations->getAnimationPart(DartGun::PivotBone);

	this->dartGunAnimations->playAnimation();

	if (GameUtils::keyExists(this->properties, GameObject::MapKeyFlipX))
	{
		this->dartGunAnimations->setFlippedX(this->properties[GameObject::MapKeyWidth].asBool());
	}

	if (GameUtils::keyExists(this->properties, GameObject::MapKeyFlipY))
	{
		this->dartGunAnimations->setFlippedY(this->properties[GameObject::MapKeyWidth].asBool());
	}

	this->addChild(this->dartNode);
	this->addChild(this->dartGunAnimations);
}

DartGun::~DartGun()
{
}

void DartGun::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void DartGun::initializePositions()
{
	super::initializePositions();
}

void DartGun::update(float dt)
{
	super::update(dt);

	this->shoot(dt);
}

Vec2 DartGun::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void DartGun::registerHackables()
{
	super::registerHackables();

	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_SWING,
			HackableCode::LateBindData(
				DartGun::MapKeyDartGun,
				Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_SetTargetAngle::create(),
				UIResources::Menus_Icons_CrossHair,
				nullptr,
				{
					{ HackableCode::Register::zax, nullptr },
					{ HackableCode::Register::zbx, nullptr }
				},
				int(HackFlags::None),
				20.0f
			)
		},
	};

	auto swingFunc = &DartGun::shoot;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

NO_OPTIMIZE void DartGun::shoot(float dt)
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([=](Squally* squally)
	{
		Vec2 squallyPos = GameUtils::getWorldCoords(squally);

		float angleBetween = -std::atan2(this->getPositionY() - squallyPos.y, this->getPositionX() - squallyPos.x) + (this->dartGunAnimations->getFlippedX() ? float(M_PI) : 0.0f);

		cannon->setRotation(MathUtils::wrappingNormalize(angleBetween, 0.0f, 2.0f * float(M_PI)) * 180.0f / float(M_PI));

		this->timeSinceLastShot += dt;

		Rect bounds = GameUtils::getScreenBounds(this);
		Size visibleSize = Director::getInstance()->getVisibleSize();

		if (bounds.getMinX() > 0 && bounds.getMaxX() < visibleSize.width && bounds.getMinY() > 0 && bounds.getMaxY() < visibleSize.height)
		{
			if (this->timeSinceLastShot > 4.0f)
			{
				this->timeSinceLastShot = 0.0f;

				float dartRotation = angleBetween * 180.0f / float(M_PI);
				Dart* dart = Dart::create(dartRotation, 256.0f, dartRotation);

				dart->setPosition3D(this->getPosition3D() + Vec3(0.0f, 64.0f, 0.0f));

				ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
					this,
					dart,
					ObjectEvents::SpawnMethod::Below,
					ObjectEvents::PositionMode::Retain
				));
			}
		}
	}), Squally::MapKeySqually);

	/*
	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZAX, angleInt);
	ASM_MOV_REG_VAR(ZBX, previousAngleInt);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SWING);
	ASM(mov ZBX, ZAX);
	ASM_NOP5();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(angleInt, ZBX);

	ASM(pop ZBX);
	ASM(pop ZAX);
	*/

	HACKABLES_STOP_SEARCH();
}
