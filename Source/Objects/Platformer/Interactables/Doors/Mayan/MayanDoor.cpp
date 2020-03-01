#include "MayanDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanGemBlue.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanGemPurple.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanGemRed.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string MayanDoor::MapKeyMayanDoor = "mayan-door";
const float MayanDoor::DoorOpenDelta = 320.0f;
const std::string MayanDoor::UnlockedSaveKey = "TEMPLE_DOOR_UNLOCKED";

MayanDoor* MayanDoor::create(ValueMap& properties)
{
	MayanDoor* instance = new MayanDoor(properties);

	instance->autorelease();

	return instance;
}

MayanDoor::MayanDoor(ValueMap& properties) : super(properties, Size(478.0f, 478.0f), Vec2(0.0f, 0.0f))
{
	this->doorFrame = Sprite::create(ObjectResources::Doors_Mayan_StoneCircleDoor);
	this->door = Sprite::create(ObjectResources::Doors_Mayan_StoneCircleDoorInner);
	this->doorContainer = Node::create();
	this->doorOpenSound = WorldSound::create();
	this->redGem = MayanGemRed::create();
	this->blueGem = MayanGemBlue::create();
	this->purpleGem = MayanGemPurple::create();

	this->doorContainer->addChild(this->door);
	this->addChild(this->redGem);
	this->addChild(this->blueGem);
	this->addChild(this->purpleGem);
	this->addChild(this->doorFrame);
	this->addChild(this->doorContainer);
	this->addChild(this->doorOpenSound);
}

MayanDoor::~MayanDoor()
{
}

void MayanDoor::initializePositions()
{
	super::initializePositions();

	const float Radius = 336.0f;

	const float RedGemAngle = 5.0f * float(M_PI) / 6.0f;
	const float PurpleGemAngle = 1.0f * float(M_PI) / 6.0f;

	this->redGem->setPosition(Vec2(Radius * std::cos(RedGemAngle), Radius * std::sin(RedGemAngle)));
	this->blueGem->setPosition(Vec2(0.0f, Radius));
	this->purpleGem->setPosition(Vec2(Radius * std::cos(PurpleGemAngle), Radius * std::sin(PurpleGemAngle)));
	this->doorFrame->setPosition(Vec2(0.0f, 0.0f));
	this->doorContainer->setPosition(Vec2(0.0f, 24.0f));
}

void MayanDoor::onObjectStateLoaded()
{
	super::onObjectStateLoaded();

	if (this->getObjectStateOrDefault(MayanDoor::UnlockedSaveKey, Value(false)).asBool())
	{
		this->unlock(false);
	}
	else
	{
		this->lock(false);
	}
}

void MayanDoor::lock(bool animate)
{
	super::lock(animate);

	this->saveObjectState(MayanDoor::UnlockedSaveKey, Value(false));
	
	float currentProgress = this->door->getPositionX() / MayanDoor::DoorOpenDelta;

	if (animate)
	{
		this->door->stopAllActions();
		this->door->runAction(MoveTo::create(5.0f * currentProgress, Vec2::ZERO));

		if (this->doorOpenSound != nullptr)
		{
			this->doorOpenSound->play();
		}
	}
	else
	{
		this->door->setPosition(Vec2::ZERO);
	}
}

void MayanDoor::unlock(bool animate)
{
	super::unlock(animate);

	this->saveObjectState(MayanDoor::UnlockedSaveKey, Value(true));

	float currentProgress = 1.0f - this->door->getPositionX() / MayanDoor::DoorOpenDelta;

	if (animate)
	{
		this->door->stopAllActions();
		this->door->runAction(MoveTo::create(5.0f * currentProgress, Vec2(MayanDoor::DoorOpenDelta, 0.0f)));
		
		if (this->doorOpenSound != nullptr)
		{
			this->doorOpenSound->play();
		}
	}
	else
	{
		this->door->setPosition(Vec2(0.0f, MayanDoor::DoorOpenDelta));
	}
}
