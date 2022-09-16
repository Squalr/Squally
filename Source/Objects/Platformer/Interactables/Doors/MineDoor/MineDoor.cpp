#include "MineDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/DecorResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string MineDoor::MapKey = "mine-door";
const std::string MineDoor::UnlockedSaveKey = "MINE_DOOR_UNLOCKED";

MineDoor* MineDoor::create(ValueMap& properties)
{
	MineDoor* instance = new MineDoor(properties);

	instance->autorelease();

	return instance;
}

MineDoor::MineDoor(ValueMap& properties) : super(properties, CSize(192.0f, 528.0f), Vec2(0.0f, 0.0f))
{
	this->doorLocked = Sprite::create(DecorResources::Mines_MineDoorClosed);
	this->door = Sprite::create(DecorResources::Mines_MineDoorTunnel);

	this->contentNode->addChild(this->doorLocked);
	this->contentNode->addChild(this->door);
}

MineDoor::~MineDoor()
{
}

void MineDoor::onEnter()
{
	super::onEnter();
	
	if (this->loadObjectStateOrDefault(MineDoor::UnlockedSaveKey, Value(true)).asBool())
	{
		this->unlock(false);
	}
	else
	{
		this->lock(false);
	}
}

void MineDoor::initializePositions()
{
	super::initializePositions();
}

void MineDoor::lock(bool animate)
{
	super::lock(animate);

	this->saveObjectState(MineDoor::UnlockedSaveKey, Value(false));
	
	this->door->setVisible(false);
	this->doorLocked->setVisible(true);
}

void MineDoor::unlock(bool animate)
{
	super::unlock(animate);

	this->saveObjectState(MineDoor::UnlockedSaveKey, Value(true));

	this->door->setVisible(true);
	this->doorLocked->setVisible(false);
}
