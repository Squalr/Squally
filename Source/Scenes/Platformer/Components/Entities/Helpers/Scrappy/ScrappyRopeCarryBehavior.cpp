#include "ScrappyRopeCarryBehavior.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Physics/CollisionObject.h"
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
	this->target = nullptr;
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

void ScrappyRopeCarryBehavior::setCarryTarget(GameObject* target)
{
	this->target = target;

	this->ropeWaist->setVisible(this->target != nullptr);
	this->rope->setVisible(this->target != nullptr);
}

void ScrappyRopeCarryBehavior::update(float dt)
{
	super::update(dt);

	if (this->target == nullptr || this->entity == nullptr)
	{
		return;
	}

	Vec3 destPosition = Vec3(
		std::cos(this->ropeRotation * float(M_PI) / 180.0f) * ScrappyRopeCarryBehavior::FixedRopeDistance,
		std::sin(this->ropeRotation * float(M_PI) / 180.0f) * ScrappyRopeCarryBehavior::FixedRopeDistance,
		0.0f
	);

	this->ropeWaist->setPosition(this->entity->getFloatNode()->getPosition() + Vec2(0.0f, 32.0f));
	this->rope->setPosition(this->entity->getFloatNode()->getPosition() + Vec2(0.0f, 32.0f));
	this->rope->setRotation(this->ropeRotation - 90.0f);

	this->ropeWaist->setFlippedX(this->entity->isFlippedX());
	this->rope->setFlippedX(this->entity->isFlippedX());

	GameUtils::setWorldCoords3D(this->target, GameUtils::getWorldCoords3D(this->entity->getAnimations()) + destPosition);
}
