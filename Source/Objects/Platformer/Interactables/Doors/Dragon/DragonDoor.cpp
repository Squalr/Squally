#include "DragonDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string DragonDoor::MapKey = "dragon-door";
const float DragonDoor::DoorOpenDelta = 242.0f;
const std::string DragonDoor::UnlockedSaveKey = "TEMPLE_DOOR_UNLOCKED";
const Vec2 DragonDoor::TeethPositionBottom = Vec2(0.0f, -160.0f - 102.0f);
const Vec2 DragonDoor::BarPositionBottom = Vec2(0.0f, 0.0f - 102.0f);

DragonDoor* DragonDoor::create(ValueMap& properties)
{
	DragonDoor* instance = new DragonDoor(properties);

	instance->autorelease();

	return instance;
}

DragonDoor::DragonDoor(ValueMap& properties) : super(properties, Size(420.0f, 528.0f), Vec2(0.0f, 0.0f))
{
	this->doorOpenSound = WorldSound::create(SoundResources::Platformer_Objects_Doors_StoneWall1);
	this->base = Sprite::create(ObjectResources::Doors_Dragon_DragonDoorBase);
	this->bars = Sprite::create(ObjectResources::Doors_Dragon_DragonDoorBars);
	this->top = Sprite::create(ObjectResources::Doors_Dragon_DragonDoorTop);
	this->teeth = Sprite::create(ObjectResources::Doors_Dragon_DragonDoorTeeth);

	this->addChild(this->base);
	this->addChild(this->bars);
	this->addChild(this->top);
	this->addChild(this->teeth);
	this->addChild(this->doorOpenSound);
}

DragonDoor::~DragonDoor()
{
}

void DragonDoor::onEnter()
{
	super::onEnter();
	
	if (this->loadObjectStateOrDefault(DragonDoor::UnlockedSaveKey, Value(true)).asBool())
	{
		this->unlock(false);
	}
	else
	{
		this->lock(false);
	}
}

void DragonDoor::initializePositions()
{
	super::initializePositions();

	this->base->setPosition(Vec2(0.0f, -160.0f));
	this->bars->setPosition(DragonDoor::BarPositionBottom);
	this->top->setPosition(Vec2(0.0f, 96.0f));
	this->teeth->setPosition(DragonDoor::TeethPositionBottom);
}

void DragonDoor::lock(bool animate)
{
	super::lock(animate);

	this->saveObjectState(DragonDoor::UnlockedSaveKey, Value(false));
	
	float currentProgress = (DragonDoor::TeethPositionBottom.y - this->teeth->getPositionY()) / DragonDoor::DoorOpenDelta;

	if (animate)
	{
		this->teeth->stopAllActions();
		this->teeth->runAction(MoveTo::create(5.0f * currentProgress, DragonDoor::TeethPositionBottom));
		this->bars->stopAllActions();
		this->bars->runAction(MoveTo::create(5.0f * currentProgress, DragonDoor::BarPositionBottom));

		this->doorOpenSound->play();
	}
	else
	{
		this->teeth->setPosition(DragonDoor::TeethPositionBottom);
		this->bars->setPosition(DragonDoor::BarPositionBottom);
	}
}

void DragonDoor::unlock(bool animate)
{
	super::unlock(animate);

	this->saveObjectState(DragonDoor::UnlockedSaveKey, Value(true));

	float currentProgress = 1.0f - (DragonDoor::TeethPositionBottom.y - this->teeth->getPositionY()) / DragonDoor::DoorOpenDelta;

	if (animate)
	{
		this->teeth->stopAllActions();
		this->teeth->runAction(MoveTo::create(5.0f * currentProgress, DragonDoor::TeethPositionBottom + Vec2(0.0f, DragonDoor::DoorOpenDelta)));
		this->bars->stopAllActions();
		this->bars->runAction(MoveTo::create(5.0f * currentProgress, DragonDoor::BarPositionBottom + Vec2(0.0f, DragonDoor::DoorOpenDelta)));
		this->doorOpenSound->play();
	}
	else
	{
		this->teeth->setPosition(DragonDoor::TeethPositionBottom + Vec2(0.0f, DragonDoor::DoorOpenDelta));
		this->bars->setPosition(DragonDoor::BarPositionBottom + Vec2(0.0f, DragonDoor::DoorOpenDelta));
	}
}
