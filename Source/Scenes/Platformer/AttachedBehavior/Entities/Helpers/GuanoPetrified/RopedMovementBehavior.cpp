#include "RopedMovementBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/HelperFollowMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/ScrappyRopeCarryBehavior.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string RopedMovementBehavior::MapKey = "roped-movement";

RopedMovementBehavior* RopedMovementBehavior::create(GameObject* owner)
{
	RopedMovementBehavior* instance = new RopedMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

RopedMovementBehavior::RopedMovementBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->scrappy = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

RopedMovementBehavior::~RopedMovementBehavior()
{
}

void RopedMovementBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	
		this->scrappy->watchForAttachedBehavior<ScrappyRopeCarryBehavior>([=](ScrappyRopeCarryBehavior* ropeCarryBehavior)
		{
			ropeCarryBehavior->setCarryTarget(this->entity);
		});
	}, Scrappy::MapKey);
	
	this->entity->watchForAttachedBehavior<HelperFollowMovementBehavior>([=](HelperFollowMovementBehavior* followBehavior)
	{
		followBehavior->disableFollow();
	});

	this->scheduleUpdate();
}

void RopedMovementBehavior::onDisable()
{
	super::onDisable();
}

void RopedMovementBehavior::update(float dt)
{
	super::update(dt);

	this->entity->getAnimations()->setFlippedX(this->scrappy->isFlippedX());
}
