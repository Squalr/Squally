#include "PivotLauncher.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Projectiles/Projectile.h"
#include "Objects/Platformer/Projectiles/ProjectilePool.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_LAUNCH_TIMER 1

const std::string PivotLauncher::PivotBone = "pivot_bone";
const std::string PivotLauncher::PropertyLaunchSpeed = "speed";
const std::string PivotLauncher::PropertyPivotTarget = "pivot-target";
const std::string PivotLauncher::PropertyFixed = "fixed";
const float PivotLauncher::DefaultLaunchSpeed = 320.0f;
const float PivotLauncher::LaunchCooldownMin = 2.0f;
const float PivotLauncher::LaunchCooldownMax = 4.0f;

PivotLauncher::PivotLauncher(ValueMap& properties, std::string animationResource) : super(properties)
{
	this->containerNode = Node::create();
	this->launcherAnimations = SmartAnimationNode::create(animationResource);
	this->projectilePool = ProjectilePool::create([=](){ return this->createProjectile(); });
	this->launchTimer = 0.0f;
	this->cannon = this->launcherAnimations->getAnimationPart(PivotLauncher::PivotBone);
	this->targetQueryKey = GameUtils::getKeyOrDefault(this->properties, PivotLauncher::PropertyPivotTarget, Value("")).asString();
	this->isFixed = GameUtils::keyExists(this->properties, PivotLauncher::PropertyFixed);
	this->fixedAngle = GameUtils::getKeyOrDefault(this->properties, PivotLauncher::PropertyFixed, Value(0.0f)).asFloat();
	this->launchSpeed = GameUtils::getKeyOrDefault(this->properties, PivotLauncher::PropertyLaunchSpeed, Value(320.0f)).asFloat();
	this->currentAngle = this->fixedAngle;
	this->target = nullptr;
	this->isAutoLaunch = true;

	this->launcherAnimations->playAnimation();
	this->launcherAnimations->setPositionY(-GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat() / 2.0f);
	this->launcherAnimations->setFlippedX(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool());
	this->launcherAnimations->setFlippedY(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipY, Value(false)).asBool());

	this->faceTarget();

	this->containerNode->addChild(this->projectilePool);
	this->containerNode->addChild(this->launcherAnimations);
	this->addChild(this->containerNode);
}

PivotLauncher::~PivotLauncher()
{
}

void PivotLauncher::onEnter()
{
	super::onEnter();

	this->listenForMapEvent(this->getListenEvent(), [=](ValueMap args)
	{
		this->shoot();
	});

	ObjectEvents::watchForObject<PlatformerEntity>(this, [=](PlatformerEntity* platformerEntity)
	{
		this->target = platformerEntity;
	}, this->targetQueryKey);

	this->scheduleUpdate();
}

void PivotLauncher::initializePositions()
{
	super::initializePositions();
}

void PivotLauncher::update(float dt)
{
	super::update(dt);

	this->faceTarget();

	// if (this->rangeCheck())
	if (this->isAutoLaunch)
	{
		this->updateShootTimer(dt);
	}
}

Vec2 PivotLauncher::getButtonOffset()
{
	const float width = 0.0f;
	const float height = -124.0f;
	const float angle = float(M_PI) * this->currentAngle / 180.0f;

	return Vec2(std::sin(angle) * width, std::cos(angle) * height);
}

void PivotLauncher::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_LAUNCH_TIMER,
			HackableCode::HackableCodeInfo(
				"pivot-launch-timer",
				Strings::Menus_Hacking_Objects_PivotLauncher_UpdateLaunchTimer_UpdateLaunchTimer::create(),
				UIResources::Menus_Icons_CrossHair,
				this->getTimerPreview(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_PivotLauncher_UpdateLaunchTimer_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Objects_PivotLauncher_UpdateLaunchTimer_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Objects_PivotLauncher_UpdateLaunchTimer_RegisterXmm1::create() },
				},
				int(HackFlags::None),
				12.0f,
				0.0f,
				this->getTimerClippy()
			)
		},
	};

	auto swingFunc = &PivotLauncher::updateShootTimer;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

Clippy* PivotLauncher::getTimerClippy()
{
	return nullptr;
}

HackablePreview* PivotLauncher::getTimerPreview()
{
	return nullptr;
}

void PivotLauncher::setAutoLaunch(bool isAutoLaunch)
{
	this->isAutoLaunch = isAutoLaunch;
}

bool PivotLauncher::rangeCheck()
{
	// It may be ideal for this to be configurable. Fixed-angle launchers can get away with this being a high value, but player-tracking launchers would want this to be low.
	static const Size Padding = Size(1024.0f, 512.0f);

	float zoom = GameCamera::getInstance()->getCameraZoomOnTarget(this);
	Size clipSize = (Director::getInstance()->getVisibleSize() + Padding) * zoom;
	Rect cameraRect = Rect(GameCamera::getInstance()->getCameraPosition() - Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), clipSize);
	Rect thisRect = GameUtils::getScreenBounds(this);

	thisRect.origin += GameUtils::getWorldCoords(this);

	return cameraRect.intersectsRect(thisRect);
}

void PivotLauncher::shoot()
{
	Projectile* projectile = this->projectilePool->getNextProjectile();

	projectile->launchTowardsTarget(this->target, this->target->getEntityCenterPoint(), 0.0f, Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, -64.0f, 0.0f));
}

void PivotLauncher::faceTarget()
{
	if (this->isFixed)
	{
		this->currentAngle = this->fixedAngle;
	}
	else if (this->target != nullptr)
	{
		Vec2 thisCoords = GameUtils::getWorldCoords(this->launcherAnimations);
		Vec2 targetCoords = GameUtils::getWorldCoords(this->target);

		const float angleBetween = -std::atan2(thisCoords.y - targetCoords.y, thisCoords.x - targetCoords.x) + (this->launcherAnimations->getFlippedX() ? float(M_PI) : 0.0f);
		const float angleNormalized = MathUtils::wrappingNormalize(float(M_PI) + angleBetween, 0.0f, 2.0f * float(M_PI));

		this->currentAngle = -angleNormalized * 180.0f / float(M_PI);
	}

	cannon->setRotation(this->currentAngle);
}

NO_OPTIMIZE void PivotLauncher::updateShootTimer(float dt)
{
	if (this->target == nullptr)
	{
		return;
	}

	if (this->launchTimer <= 0.0f)
	{
		this->launchTimer = RandomHelper::random_real(PivotLauncher::LaunchCooldownMin, PivotLauncher::LaunchCooldownMax);

		this->projectilePool->getNextProjectile();
	}

	volatile float* timePtr = &this->launchTimer;
	volatile float* dtPtr = &dt;

	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZAX, timePtr);
	ASM_MOV_REG_VAR(ZBX, dtPtr);
	ASM(movss xmm0, [ZAX])
	ASM(movss xmm1, [ZBX])

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_LAUNCH_TIMER);
	ASM(subps xmm0, xmm1);
	ASM(movss [ZAX], xmm0);
	ASM_NOP10();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZAX);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
