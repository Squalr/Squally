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
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string MineDoor::MapKey = "mine-door";
const float MineDoor::DoorOpenDelta = 320.0f;
const std::string MineDoor::UnlockedSaveKey = "MINE_DOOR_UNLOCKED";

MineDoor* MineDoor::create(ValueMap& properties)
{
	MineDoor* instance = new MineDoor(properties);

	instance->autorelease();

	return instance;
}

MineDoor::MineDoor(ValueMap& properties) : super(properties, CSize(192.0f, 528.0f), Vec2(0.0f, 0.0f))
{
	this->doorOpenSound = WorldSound::create(SoundResources::Platformer_Objects_Doors_StoneWall1);
	this->back = Sprite::create(DecorResources::Mines_MineDoorTunnel);
	this->door = Sprite::create(DecorResources::Mines_MineDoorClosed);
	this->doorClip = SmartClippingNode::create(this->door, CSize(212.0f, 290.0f));
	

	this->contentNode->addChild(this->back);
	this->contentNode->addChild(this->doorClip);

	this->addChild(this->doorOpenSound);
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

	this->doorClip->setPosition(Vec2(0.0f, -50.0f));
	this->door->setPosition(Vec2(0.0f, 50.0f));
}

void MineDoor::lock(bool animate)
{
	super::lock(animate);

	this->saveObjectState(MineDoor::UnlockedSaveKey, Value(false));
	
	float currentProgress = this->door->getPositionY() / MineDoor::DoorOpenDelta;

	if (animate)
	{
		this->door->stopAllActions();
		this->door->runAction(MoveTo::create(5.0f * currentProgress, Vec2::ZERO));

		this->doorOpenSound->play();
	}
	else
	{
		this->door->setPosition(Vec2::ZERO);
	}
}

void MineDoor::unlock(bool animate)
{
	super::unlock(animate);

	this->saveObjectState(MineDoor::UnlockedSaveKey, Value(true));

	float currentProgress = 1.0f - this->door->getPositionY() / MineDoor::DoorOpenDelta;

	if (animate)
	{
		this->door->stopAllActions();
		this->door->runAction(MoveTo::create(5.0f * currentProgress, Vec2(0.0f, MineDoor::DoorOpenDelta)));
		this->doorOpenSound->play();
	}
	else
	{
		this->door->setPosition(Vec2(0.0f, MineDoor::DoorOpenDelta));
	}
}
