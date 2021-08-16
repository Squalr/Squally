#include "ScrappyRopeCarryBehavior.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Movement/SquallyMovementBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string ScrappyRopeCarryBehavior::MapKey = "rope-carry";
const float ScrappyRopeCarryBehavior::FixedRopeDistance = 256.0f;

ScrappyRopeCarryBehavior* ScrappyRopeCarryBehavior::create(GameObject* owner)
{
	ScrappyRopeCarryBehavior* instance = new ScrappyRopeCarryBehavior(owner);

	instance->autorelease();

	return instance;
}

ScrappyRopeCarryBehavior::ScrappyRopeCarryBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->carriedObject = nullptr;
	this->rope = Sprite::create(ObjectResources::Cinematic_ScrappyRope_Rope);
	this->ropeWaist = Sprite::create(ObjectResources::Cinematic_ScrappyRope_WaistRope);
	this->ropeRotation = 270.0f;

	this->ropeWaist->setVisible(false);
	this->rope->setVisible(false);
	this->rope->setAnchorPoint(Vec2(0.5f, 0.0f));

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->rope);
	this->addChild(this->ropeWaist);
}

ScrappyRopeCarryBehavior::~ScrappyRopeCarryBehavior()
{
}

void ScrappyRopeCarryBehavior::onLoad()
{
	this->scheduleUpdate();
}

void ScrappyRopeCarryBehavior::onDisable()
{
	super::onDisable();
}

void ScrappyRopeCarryBehavior::setCarriedObject(GameObject* carriedObject)
{
	this->carriedObject = carriedObject;

	this->ropeWaist->setVisible(this->carriedObject != nullptr);
	this->rope->setVisible(this->carriedObject != nullptr);
}

void ScrappyRopeCarryBehavior::update(float dt)
{
	super::update(dt);

	if (this->carriedObject == nullptr || this->entity == nullptr)
	{
		return;
	}

	static const Vec2 RopeAttachOffset = Vec2(0.0f, 32.0f);
	static const float SwingGravity = -768.0f;

	Vec2 floatOffset = this->entity->getFloatNode()->getPosition();

	// Offset rope positions by float positions
	this->ropeWaist->setPosition(floatOffset + RopeAttachOffset);
	this->rope->setPosition(floatOffset + RopeAttachOffset);

	Vec3 ropeScrappyAttachPoint3D = GameUtils::getWorldCoords3D(this->entity->getFloatNode()) + Vec3(RopeAttachOffset.x, RopeAttachOffset.y, 0.0f);
	Vec2 ropeScrappyAttachPoint2D = Vec2(ropeScrappyAttachPoint3D.x, ropeScrappyAttachPoint3D.y);
	Vec2 carriedObjectCoords2D = GameUtils::getWorldCoords(this->carriedObject);
	Vec2 ropeCarriedObjectAttachPoint2D = carriedObjectCoords2D + RopeAttachOffset;

	ropeCarriedObjectAttachPoint2D.y += SwingGravity * dt;

	// Rope visual updates
	this->ropeRotation = -std::atan2(
		ropeScrappyAttachPoint2D.y - ropeCarriedObjectAttachPoint2D.y,
		ropeScrappyAttachPoint2D.x - ropeCarriedObjectAttachPoint2D.x) * 180.0f / float(M_PI);
	this->rope->setRotation(this->ropeRotation - 90.0f);
	this->ropeWaist->setFlippedX(this->entity->isFlippedX());
	this->rope->setFlippedX(this->entity->isFlippedX());

	// Compute final position
	Vec2 closestPointOnRope2D = AlgoUtils::pointOnCircle(ropeScrappyAttachPoint2D, ScrappyRopeCarryBehavior::FixedRopeDistance, ropeCarriedObjectAttachPoint2D);
	Vec3 closestPointOnRope3D = Vec3(closestPointOnRope2D.x, closestPointOnRope2D.y, ropeScrappyAttachPoint3D.z);

	GameUtils::setWorldCoords3D(this->carriedObject, closestPointOnRope3D - Vec3(RopeAttachOffset.x, RopeAttachOffset.y, 0.0f));
}
