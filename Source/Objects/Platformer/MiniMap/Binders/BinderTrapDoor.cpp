#include "BinderTrapDoor.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Interactables/Doors/TrapDoor/TrapDoor.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;


BinderTrapDoor* BinderTrapDoor::create()
{
	BinderTrapDoor* instance = new BinderTrapDoor();

	instance->autorelease();

	return instance;
}

BinderTrapDoor::BinderTrapDoor() : super()
{
}

BinderTrapDoor::~BinderTrapDoor()
{
}

void BinderTrapDoor::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	super::bindTo(miniMapObject, gameObject);

	this->trapDoor = dynamic_cast<TrapDoor*>(gameObject);
}

void BinderTrapDoor::update(float dt)
{
	super::update(dt);

	if (this->trapDoor == nullptr)
	{
		return;
	}

	float flipMultiplier = this->trapDoor->isFlipped ? -1.0f : 1.0f;

	this->miniMapObject->drawNode->setPositionX(this->trapDoor->destinationProgress * TrapDoor::DoorOpenDelta * flipMultiplier);
}
