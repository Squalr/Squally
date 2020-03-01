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
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanGemBlue.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanGemPurple.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanGemRed.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
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

const std::string MayanDoor::MapKeyMayanDoor = "mayan-door";
const float MayanDoor::DoorOpenDelta = 320.0f;
const std::string MayanDoor::EventMayanDoorUnlock = "mayan-door-unlock";
const std::string MayanDoor::SaveKeyRedGem = "SAVE_KEY_RED_GEM";
const std::string MayanDoor::SaveKeyBlueGem = "SAVE_KEY_BLUE_GEM";
const std::string MayanDoor::SaveKeyPurpleGem = "SAVE_KEY_PURPLE_GEM";
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
	this->redGem = MayanGemRed::create();
	this->blueGem = MayanGemBlue::create();
	this->purpleGem = MayanGemPurple::create();
	this->turninHitbox = CollisionObject::create(
		CollisionObject::createBox(Size(640.0f, 256.0f)),
		(CollisionType)PlatformerCollisionType::Trigger,
		CollisionObject::Properties(false, false),
		Color4F::WHITE
	);
	this->inventory = nullptr;
	this->isUnlocking = false;

	this->doorContainer->addChild(this->doorFrame);
	this->doorContainer->addChild(this->innerContainer);
	this->innerContainer->addChild(this->doorArrow);
	this->innerContainer->addChild(this->door);
	this->addChild(this->redGem);
	this->addChild(this->blueGem);
	this->addChild(this->purpleGem);
	this->addChild(this->doorContainer);
	this->addChild(this->doorOpenSound);
	this->addChild(this->turninHitbox);
}

MayanDoor::~MayanDoor()
{
}

void MayanDoor::onEnter()
{
	super::onEnter();
	
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
		});
	}, Squally::MapKeySqually);
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
	this->doorArrow->setPosition(Vec2(0.0f, 180.0f));
	this->doorFrame->setPosition(Vec2(0.0f, 0.0f));
	this->turninHitbox->setPosition(Vec2(0.0f, (256.0f - 478.0f) / 2.0f));
	this->innerContainer->setPosition(Vec2(0.0f, 0.0f));
}

void MayanDoor::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(MayanDoor::EventMayanDoorUnlock, [=](ValueMap args)
	{
		this->tryUnlock();
	});

	this->turninHitbox->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->tryTakeGems();

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void MayanDoor::onObjectStateLoaded()
{
	super::onObjectStateLoaded();

	if (this->getObjectStateOrDefault(MayanDoor::SaveKeyUnlocked, Value(false)).asBool())
	{
		this->unlock(false);
	}
	else
	{
		this->lock(false);
	}
	
	if (this->getObjectStateOrDefault(MayanDoor::SaveKeyRedGem, Value(false)).asBool())
	{
		this->redGem->enableGem();
	}

	if (this->getObjectStateOrDefault(MayanDoor::SaveKeyBlueGem, Value(false)).asBool())
	{
		this->blueGem->enableGem();
	}

	if (this->getObjectStateOrDefault(MayanDoor::SaveKeyPurpleGem, Value(false)).asBool())
	{
		this->purpleGem->enableGem();
	}
}

void MayanDoor::registerHackables()
{
	super::registerHackables();
	
	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_GEM_RED,
			HackableCode::HackableCodeInfo(
				"mayan-gem-red",
				nullptr, // Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_SetTargetAngle::create(),
				UIResources::Menus_Icons_Ruby,
				nullptr, // PendulumBladeSetAnglePreview::create(),
				{
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_RegisterEbx::create() }
				},
				int(HackFlags::None),
				15.0f,
				0.0f,
				nullptr // this->pendulumBladeClippy
			)
		},
		{
			LOCAL_FUNC_ID_GEM_BLUE,
			HackableCode::HackableCodeInfo(
				"mayan-gem-blue",
				nullptr, // Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_SetTargetAngle::create(),
				UIResources::Menus_Icons_Diamond,
				nullptr, // PendulumBladeSetAnglePreview::create(),
				{
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_RegisterEbx::create() }
				},
				int(HackFlags::None),
				15.0f,
				0.0f,
				nullptr // this->pendulumBladeClippy
			)
		},
		{
			LOCAL_FUNC_ID_GEM_PURPLE,
			HackableCode::HackableCodeInfo(
				"mayan-gem-purple",
				nullptr, // Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_SetTargetAngle::create(),
				UIResources::Menus_Icons_CrystalShard,
				nullptr, // PendulumBladeSetAnglePreview::create(),
				{
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_RegisterEbx::create() }
				},
				int(HackFlags::None),
				15.0f,
				0.0f,
				nullptr // this->pendulumBladeClippy
			)
		},
	};

	auto gemFuncRed = &MayanDoor::runGemRed;
	std::vector<HackableCode*> hackablesRed = HackableCode::create((void*&)gemFuncRed, codeInfoMap);

	for (auto next : hackablesRed)
	{
		this->registerCode(next);
	}

	auto gemFuncBlue = &MayanDoor::runGemBlue;
	std::vector<HackableCode*> hackablesBlue = HackableCode::create((void*&)gemFuncBlue, codeInfoMap);

	for (auto next : hackablesBlue)
	{
		this->registerCode(next);
	}

	auto gemFuncPurple = &MayanDoor::runGemPurple;
	std::vector<HackableCode*> hackablesPurple = HackableCode::create((void*&)gemFuncPurple, codeInfoMap);

	for (auto next : hackablesPurple)
	{
		this->registerCode(next);
	}
}

void MayanDoor::tryTakeGems()
{
	if (this->inventory == nullptr)
	{
		return;
	}

	std::vector<MayanGemRedItem*> redGems = this->inventory->getItemsOfType<MayanGemRedItem>();
	std::vector<MayanGemBlueItem*> blueGems = this->inventory->getItemsOfType<MayanGemBlueItem>();
	std::vector<MayanGemPurpleItem*> purpleGems = this->inventory->getItemsOfType<MayanGemPurpleItem>();

	if (!redGems.empty())
	{
		PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(redGems.back()));
	}
	else if (!blueGems.empty())
	{
		PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(blueGems.back()));
	}
	else if (!purpleGems.empty())
	{
		PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(purpleGems.back()));
	}

	if (!redGems.empty())
	{
		inventory->tryRemove(redGems.back());

		this->saveObjectState(MayanDoor::SaveKeyRedGem, Value(true));
		this->redGem->enableGem();
	}

	if (!blueGems.empty())
	{
		inventory->tryRemove(blueGems.back());

		this->saveObjectState(MayanDoor::SaveKeyBlueGem, Value(true));
		this->blueGem->enableGem();
	}

	if (!purpleGems.empty())
	{
		inventory->tryRemove(purpleGems.back());

		this->saveObjectState(MayanDoor::SaveKeyPurpleGem, Value(true));
		this->purpleGem->enableGem();
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
	int indexBlue = this->runGemRed(indexRed);
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

	float delayRed = float(std::min(std::abs(indexRed - 0), std::abs(indexRed - 0))) * RotationSpeedPerUnit;
	float delayBlue = float(std::min(std::abs(indexRed - indexBlue), std::abs(indexRed - indexBlue))) * RotationSpeedPerUnit;
	float delayPurple = float(std::min(std::abs(indexPurple - indexBlue), std::abs(indexBlue - indexPurple))) * RotationSpeedPerUnit;
	float delayReturn = float(std::min(std::abs(indexPurple - 0), std::abs(0 - indexPurple))) * RotationSpeedPerUnitReturn;

	this->innerContainer->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->redGem->runFX();
		}),
		RotateTo::create(delayRed, rotationRed),
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->blueGem->runFX();
		}),
		RotateTo::create(delayBlue, rotationBlue),
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->purpleGem->runFX();
		}),
		RotateTo::create(delayPurple, rotationPurple),
		DelayTime::create(0.5f),
		RotateTo::create(delayReturn, rotationReturn),
		CallFunc::create([=]()
		{
			this->isUnlocking = false;
		}),
		nullptr
	));
}

void MayanDoor::lock(bool animate)
{
	super::lock(animate);

	this->saveObjectState(MayanDoor::SaveKeyUnlocked, Value(false));
	
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

	this->saveObjectState(MayanDoor::SaveKeyUnlocked, Value(true));

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

NO_OPTIMIZE int MayanDoor::runGemRed(int currentIndex)
{
	volatile int newIndex = currentIndex;

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZBX, newIndex);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GEM_RED);
	ASM(mov ZBX, 4);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(newIndex, ZBX);

	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(newIndex, 0, 11);
}
END_NO_OPTIMIZE

NO_OPTIMIZE int MayanDoor::runGemBlue(int currentIndex)
{
	volatile int newIndex = currentIndex;

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZBX, newIndex);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GEM_BLUE);
	ASM(add ZBX, 7);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(newIndex, ZBX);

	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(newIndex, 0, 11);
}
END_NO_OPTIMIZE

NO_OPTIMIZE int MayanDoor::runGemPurple(int currentIndex)
{
	volatile int newIndex = currentIndex;

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZBX, newIndex);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GEM_PURPLE);
	ASM(sub ZBX, 5);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(newIndex, ZBX);

	ASM(pop ZBX);

	HACKABLES_STOP_SEARCH();

	return MathUtils::clamp(newIndex, 0, 11);
}
END_NO_OPTIMIZE
