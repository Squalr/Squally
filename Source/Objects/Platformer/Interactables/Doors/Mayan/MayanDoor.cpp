#include "MayanDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_GEM_RED 1
#define LOCAL_FUNC_ID_GEM_BLUE 2
#define LOCAL_FUNC_ID_GEM_PURPLE 3

const std::string MayanDoor::MapKey = "mayan-door";
const float MayanDoor::DoorOpenDelta = 420.0f;
const std::string MayanDoor::EventMayanDoorUnlock = "mayan-door-unlock";
const std::string MayanDoor::MapEventResetPuzzle = "reset-puzzle";
const std::string MayanDoor::MapEventPush = "EVENT_STONE_PUZZLE_PUSH";
const std::string MayanDoor::MapEventPop = "EVENT_STONE_PUZZLE_POP";
const std::string MayanDoor::MapEventPopRet = "EVENT_STONE_PUZZLE_POP_RET";
const std::string MayanDoor::PropertyRegister = "register";
const std::string MayanDoor::PropertyValue = "value";
const std::string MayanDoor::SaveKeyUnlocked = "SAVE_KEY_UNLOCKED";

MayanDoor* MayanDoor::create(ValueMap& properties)
{
	MayanDoor* instance = new MayanDoor(properties);

	instance->autorelease();

	return instance;
}

MayanDoor::MayanDoor(ValueMap& properties) : super(properties, Size(478.0f, 478.0f), Vec2(0.0f, 0.0f))
{
	this->doorArrow = Sprite::create(ObjectResources::Doors_Mayan_StoneCircleDoorArrow);
	this->doorFrame = Sprite::create(ObjectResources::Doors_Mayan_StoneCircleDoor);
	this->door = Sprite::create(ObjectResources::Doors_Mayan_StoneCircleDoorInner);
	this->innerContainer = Node::create();
	this->doorContainer = Node::create();
	this->doorOpenSound = WorldSound::create();
	this->inventory = nullptr;
	this->isUnlocking = false;

	this->doorContainer->addChild(this->doorFrame);
	this->doorContainer->addChild(this->innerContainer);
	this->innerContainer->addChild(this->doorArrow);
	this->innerContainer->addChild(this->door);
	this->addChild(this->doorContainer);
	this->addChild(this->doorOpenSound);
}

MayanDoor::~MayanDoor()
{
}

void MayanDoor::onEnter()
{
	super::onEnter();
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
		});
	}, Squally::MapKey);

	this->loadGems();
}

void MayanDoor::initializePositions()
{
	super::initializePositions();

	const float Radius = 356.0f;
	const float RedGemAngle = 4.0f * float(M_PI) / 6.0f;
	const float PurpleGemAngle = 2.0f * float(M_PI) / 6.0f;

	this->doorArrow->setPosition(Vec2(0.0f, 180.0f));
	this->doorFrame->setPosition(Vec2(0.0f, 0.0f));
	this->innerContainer->setPosition(Vec2(0.0f, 0.0f));
}

void MayanDoor::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(MayanDoor::EventMayanDoorUnlock, [=](ValueMap args)
	{
		if (this->isLocked)
		{
			this->tryUnlock();
		}
	});
}

void MayanDoor::loadGems()
{
	if (this->loadObjectStateOrDefault(MayanDoor::SaveKeyUnlocked, Value(false)).asBool())
	{
		this->unlock(false);
	}
	else
	{
		this->lock(false);
	}
}

void MayanDoor::tryUnlock()
{
	if (this->isUnlocking)
	{
		return;
	}

	this->isUnlocking = true;

	int index = 0;
	int indexRed = this->runGemRed(index);
	int indexBlue = this->runGemBlue(indexRed);
	int indexPurple = this->runGemPurple(indexBlue);

	auto getRotation = [=](int rotationIndex)
	{
		return -float(rotationIndex) / 12.0f * 360.0f;
	};

	const float RotationSpeedPerUnit = 0.25f;
	const float RotationSpeedPerUnitReturn = 0.5f;
	float rotationRed = getRotation(indexRed);
	float rotationBlue = getRotation(indexBlue);
	float rotationPurple = getRotation(indexPurple);
	float rotationReturn = getRotation(0);

	auto getDist = [=](int indexFrom, int indexTo)
	{
		int distBetweenWrapped = ((indexFrom < 6) ? indexFrom : (12 - indexFrom)) + ((indexTo < 6) ? indexTo : (12 - indexTo));
		int distBetween = std::abs(indexFrom - indexTo);
		
		return float(std::min(distBetweenWrapped, distBetween));
	};

	float delayRed = std::max(getDist(indexRed, 0) * RotationSpeedPerUnit, RotationSpeedPerUnit);
	float delayBlue = std::max(getDist(indexRed, indexBlue) * RotationSpeedPerUnit, RotationSpeedPerUnit);
	float delayPurple = std::max(getDist(indexBlue, indexPurple) * RotationSpeedPerUnit, RotationSpeedPerUnit);
	float delayReturn = std::max(getDist(indexPurple, 0) * RotationSpeedPerUnitReturn, RotationSpeedPerUnitReturn);

	this->innerContainer->runAction(Sequence::create(
		RotateTo::create(delayRed, rotationRed),
		CallFunc::create([=]()
		{
			// this->redGem->runFX();
		}),
		DelayTime::create(0.5f),
		RotateTo::create(delayBlue, rotationBlue),
		CallFunc::create([=]()
		{
			// this->blueGem->runFX();
		}),
		DelayTime::create(0.5f),
		RotateTo::create(delayPurple, rotationPurple),
		CallFunc::create([=]()
		{
			// this->purpleGem->runFX();
		}),
		DelayTime::create(0.5f),
		RotateTo::create(delayReturn, rotationReturn),
		CallFunc::create([=]()
		{
			this->unlock(true);

			this->isUnlocking = false;
		}),
		nullptr
	));
}

void MayanDoor::lock(bool animate)
{
	super::lock(animate);

	this->saveObjectState(MayanDoor::SaveKeyUnlocked, Value(false));

	this->toggleHackable(true);
	
	float currentProgress = this->doorContainer->getPositionX() / MayanDoor::DoorOpenDelta;

	if (animate)
	{
		this->doorContainer->stopAllActions();
		this->doorContainer->runAction(MoveTo::create(5.0f * currentProgress, Vec2::ZERO));
		this->doorContainer->runAction(RotateTo::create(5.0f * currentProgress, 0.0f));

		if (this->doorOpenSound != nullptr)
		{
			this->doorOpenSound->play();
		}
	}
	else
	{
		this->doorContainer->setPosition(Vec2::ZERO);
		this->doorContainer->setRotation(0.0f);
	}
}

void MayanDoor::unlock(bool animate)
{
	super::unlock(animate);

	this->saveObjectState(MayanDoor::SaveKeyUnlocked, Value(true));

	this->toggleHackable(false);

	float currentProgress = 1.0f - this->doorContainer->getPositionX() / MayanDoor::DoorOpenDelta;

	if (animate)
	{
		this->doorContainer->stopAllActions();
		this->doorContainer->runAction(MoveTo::create(5.0f * currentProgress, Vec2(MayanDoor::DoorOpenDelta, 0.0f)));
		this->doorContainer->runAction(RotateTo::create(5.0f * currentProgress, 180.0f));
		
		if (this->doorOpenSound != nullptr)
		{
			this->doorOpenSound->play();
		}
	}
	else
	{
		this->doorContainer->setPosition(Vec2(MayanDoor::DoorOpenDelta, 0.0f));
		this->doorContainer->setRotation(180.0f);
	}
}

NO_OPTIMIZE int MayanDoor::runGemRed(int currentIndex)
{
	volatile int newIndex = currentIndex;

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ebx, newIndex);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GEM_RED);
	ASM(mov ZBX, 4);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(newIndex, ebx);

	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(newIndex, 0, 11);
}
END_NO_OPTIMIZE

NO_OPTIMIZE int MayanDoor::runGemBlue(int currentIndex)
{
	volatile int newIndex = currentIndex;

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ebx, newIndex);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GEM_BLUE);
	ASM(add ZBX, 7);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(newIndex, ebx);

	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(newIndex, 0, 11);
}
END_NO_OPTIMIZE

NO_OPTIMIZE int MayanDoor::runGemPurple(int currentIndex)
{
	volatile int newIndex = currentIndex;

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ebx, newIndex);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GEM_PURPLE);
	ASM(sub ZBX, 5);
	ASM_NOP8();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(newIndex, ebx);

	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(newIndex, 0, 11);
}
END_NO_OPTIMIZE
