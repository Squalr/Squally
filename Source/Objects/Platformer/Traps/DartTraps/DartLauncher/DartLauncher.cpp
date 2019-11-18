#include "DartLauncher.h"

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

const std::string DartLauncher::MapKeyDartLauncher = "dart-launcher";

DartLauncher* DartLauncher::create(ValueMap& properties)
{
	DartLauncher* instance = new DartLauncher(properties);

	instance->autorelease();

	return instance;
}

DartLauncher::DartLauncher(ValueMap& properties) : super(properties)
{
	this->launcherContainer = Node::create();
	this->launcherSprite = Sprite::create(ObjectResources::Traps_DartLauncher_DartLauncher);
	this->rotation = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyRotation, Value(0.0f)).asFloat();
	this->timeSinceLastShot = 0.0f;

	this->launcherSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->launcherSprite->setPositionY(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat() / 2.0f);

	if (GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipY, Value(false)).asBool())
	{
		this->rotation += 180.0f;
	}

	this->launcherContainer->setRotation(this->rotation);

	this->launcherContainer->addChild(this->launcherSprite);
	this->addChild(this->launcherContainer);
}

DartLauncher::~DartLauncher()
{
}

void DartLauncher::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void DartLauncher::initializePositions()
{
	super::initializePositions();
}

void DartLauncher::update(float dt)
{
	super::update(dt);

	this->shoot(dt);
}

Vec2 DartLauncher::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void DartLauncher::registerHackables()
{
	super::registerHackables();

	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_SWING,
			HackableCode::LateBindData(
				DartLauncher::MapKeyDartLauncher,
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

	auto swingFunc = &DartLauncher::shoot;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

NO_OPTIMIZE void DartLauncher::shoot(float dt)
{
	/*
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

				Dart* dart = Dart::create(angleBetween * 180.0f / float(M_PI), 256.0f);

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
