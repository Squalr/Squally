#include "LookAtSquallyBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string LookAtSquallyBehavior::MapKeyAttachedBehavior = "face-squally";

LookAtSquallyBehavior* LookAtSquallyBehavior::create(GameObject* owner)
{
	LookAtSquallyBehavior* instance = new LookAtSquallyBehavior(owner);

	instance->autorelease();

	return instance;
}

LookAtSquallyBehavior::LookAtSquallyBehavior(GameObject* owner) : super(owner)
{
	this->npc = dynamic_cast<PlatformerFriendly*>(owner);

	if (this->npc == nullptr)
	{
		this->invalidate();
	}

	this->squally = nullptr;
}

LookAtSquallyBehavior::~LookAtSquallyBehavior()
{
}

void LookAtSquallyBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
}

void LookAtSquallyBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr)
	{
		return;
	}

	if (this->npc->getPositionX() > GameUtils::getWorldCoords(this->squally).x)
	{
		this->npc->getAnimations()->setFlippedX(true);
	}
	else
	{
		this->npc->getAnimations()->setFlippedX(false);
	}
}
