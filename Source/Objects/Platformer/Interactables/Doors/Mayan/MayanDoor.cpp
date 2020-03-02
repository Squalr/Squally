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
const std::string MayanDoor::SaveKeyRedGemAnswer = "SAVE_KEY_RED_GEM_ANSWER";
const std::string MayanDoor::SaveKeyBlueGemAnswer = "SAVE_KEY_BLUE_GEM_ANSWER";
const std::string MayanDoor::SaveKeyPurpleGemAnswer = "SAVE_KEY_PURPLE_GEM_ANSWER";

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
	this->redGemAnswer = 0;
	this->blueGemAnswer = 0;
	this->purpleGemAnswer = 0;

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

	int redDefault = 0;
	int blueDefault = 0;
	int purpleDefault = 0;

	// 4, 11, 6 is the default combo. The answer can be anything except this.
	do
	{
		redDefault = RandomHelper::random_int(0, 11);
		blueDefault = RandomHelper::random_int(0, 11);
		purpleDefault = RandomHelper::random_int(0, 11);
	} while (redDefault == 4 && blueDefault == 11 && purpleDefault == 6);

	this->redGemAnswer = this->getObjectStateOrDefault(MayanDoor::SaveKeyRedGemAnswer, Value(redDefault)).asInt();
	this->blueGemAnswer = this->getObjectStateOrDefault(MayanDoor::SaveKeyBlueGemAnswer, Value(blueDefault)).asInt();
	this->purpleGemAnswer = this->getObjectStateOrDefault(MayanDoor::SaveKeyPurpleGemAnswer, Value(purpleDefault)).asInt();

	this->redGem->loadAnswer(this->redGemAnswer);
	this->blueGem->loadAnswer(this->blueGemAnswer);
	this->purpleGem->loadAnswer(this->purpleGemAnswer);

	this->saveObjectState(MayanDoor::SaveKeyRedGemAnswer, Value(this->redGemAnswer));
	this->saveObjectState(MayanDoor::SaveKeyBlueGemAnswer, Value(this->blueGemAnswer));
	this->saveObjectState(MayanDoor::SaveKeyPurpleGemAnswer, Value(this->purpleGemAnswer));

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
				Strings::Menus_Hacking_Objects_MayanDoor_Combination1::create(),
				UIResources::Menus_Icons_Ruby,
				nullptr, // PendulumBladeSetAnglePreview::create(),
				{
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_MayanDoor_RegisterEbx::create() }
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
				Strings::Menus_Hacking_Objects_MayanDoor_Combination2::create(),
				UIResources::Menus_Icons_Diamond,
				nullptr, // PendulumBladeSetAnglePreview::create(),
				{
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_MayanDoor_RegisterEbx::create() }
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
				Strings::Menus_Hacking_Objects_MayanDoor_Combination3::create(),
				UIResources::Menus_Icons_CrystalShard,
				nullptr, // PendulumBladeSetAnglePreview::create(),
				{
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_MayanDoor_RegisterEbx::create() }
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

	float delayRed = std::max(float(std::min(std::abs(indexRed - 0), std::abs(indexRed - 0))) * RotationSpeedPerUnit, RotationSpeedPerUnit);
	float delayBlue = std::max(float(std::min(std::abs(indexRed - indexBlue), std::abs(indexRed - indexBlue))) * RotationSpeedPerUnit, RotationSpeedPerUnit);
	float delayPurple = std::max(float(std::min(std::abs(indexPurple - indexBlue), std::abs(indexBlue - indexPurple))) * RotationSpeedPerUnit, RotationSpeedPerUnit);
	float delayReturn = std::max(float(std::min(std::abs(indexPurple - 0), std::abs(0 - indexPurple))) * RotationSpeedPerUnitReturn, RotationSpeedPerUnitReturn);

	this->innerContainer->runAction(Sequence::create(
		RotateTo::create(delayRed, rotationRed),
		CallFunc::create([=]()
		{
			this->redGem->runFX();
		}),
		DelayTime::create(0.5f),
		RotateTo::create(delayBlue, rotationBlue),
		CallFunc::create([=]()
		{
			this->blueGem->runFX();
		}),
		DelayTime::create(0.5f),
		RotateTo::create(delayPurple, rotationPurple),
		CallFunc::create([=]()
		{
			this->purpleGem->runFX();
		}),
		DelayTime::create(0.5f),
		RotateTo::create(delayReturn, rotationReturn),
		CallFunc::create([=]()
		{
			if (indexRed == this->redGemAnswer && indexBlue == this->blueGemAnswer && indexPurple == this->purpleGemAnswer)
			{
				this->unlock(true);
			}

			this->isUnlocking = false;
		}),
		nullptr
	));
}

void MayanDoor::lock(bool animate)
{
	super::lock(animate);

	this->saveObjectState(MayanDoor::SaveKeyUnlocked, Value(false));
	
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
