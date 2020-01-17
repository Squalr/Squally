#include "PivotLauncher.h"

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
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_LAUNCH 1

const std::string PivotLauncher::PivotBone = "pivot_bone";
const std::string PivotLauncher::PropertyLaunchSpeed = "speed";
const float PivotLauncher::DefaultLaunchSpeed = 320.0f;
const float PivotLauncher::LaunchCooldownMin = 2.0f;
const float PivotLauncher::LaunchCooldownMax = 4.0f;

PivotLauncher::PivotLauncher(ValueMap& properties, std::string animationResource) : super(properties)
{
	this->projectileNode = Node::create();
	this->launcherAnimations = SmartAnimationNode::create(animationResource);
	this->timeSinceLastShot = 0.0f;
	this->cannon = this->launcherAnimations->getAnimationPart(PivotLauncher::PivotBone);

	this->launcherAnimations->playAnimation();

	if (GameUtils::keyExists(this->properties, GameObject::MapKeyFlipX))
	{
		this->launcherAnimations->setFlippedX(this->properties[GameObject::MapKeyWidth].asBool());
	}

	if (GameUtils::keyExists(this->properties, GameObject::MapKeyFlipY))
	{
		this->launcherAnimations->setFlippedY(this->properties[GameObject::MapKeyWidth].asBool());
	}

	this->addChild(this->projectileNode);
	this->addChild(this->launcherAnimations);
}

PivotLauncher::~PivotLauncher()
{
}

void PivotLauncher::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void PivotLauncher::initializePositions()
{
	super::initializePositions();
}

void PivotLauncher::update(float dt)
{
	super::update(dt);

	this->shoot(dt);
}

Vec2 PivotLauncher::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void PivotLauncher::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_LAUNCH,
			HackableCode::HackableCodeInfo(
				"PivotLauncher",
				Strings::Menus_Hacking_Objects_PivotLauncher_SetTargetAngle_SetTargetAngle::create(),
				UIResources::Menus_Icons_CrossHair,
				nullptr,
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_PivotLauncher_SetTargetAngle_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_PivotLauncher_SetTargetAngle_RegisterEbx::create() },
				},
				int(HackFlags::None),
				20.0f
			)
		},
	};

	auto swingFunc = &PivotLauncher::shoot;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, codeInfoMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

NO_OPTIMIZE void PivotLauncher::shoot(float dt)
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([=](Squally* squally)
	{
		Vec2 squallyPos = GameUtils::getWorldCoords(squally);

		float angleBetween = -std::atan2(this->getPositionY() - squallyPos.y, this->getPositionX() - squallyPos.x) + (this->launcherAnimations->getFlippedX() ? float(M_PI) : 0.0f);

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
				/*
				Dart* dart = Dart::create(dartRotation, 256.0f);

				dart->setPosition3D(this->getPosition3D() + Vec3(0.0f, 64.0f, 0.0f));

				ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
					this,
					dart,
					ObjectEvents::SpawnMethod::Below,
					ObjectEvents::PositionMode::Retain
				));
				*/
			}
		}
	}), Squally::MapKeySqually);

	/*
	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZAX, angleInt);
	ASM_MOV_REG_VAR(ZBX, previousAngleInt);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_LAUNCH);
	ASM(mov ZBX, ZAX);
	ASM_NOP5();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(angleInt, ZBX);

	ASM(pop ZBX);
	ASM(pop ZAX);
	*/

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
