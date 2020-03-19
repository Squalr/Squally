#include "ChestBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Objects/Platformer/ItemPools/ChestPools/ChestPoolDeserializer.h"
#include "Objects/Platformer/ItemPools/ErrorPool.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ChestBase::PropertyRewardPool = "reward-pool";
const std::string ChestBase::SaveKeyIsOpen = "SAVE_KEY_IS_OPEN";

ChestBase::ChestBase(ValueMap& properties, Size interactSize) : super(properties)
{
	this->interactCollision = CollisionObject::create(CollisionObject::createBox(interactSize), (CollisionType)PlatformerCollisionType::Collectable, CollisionObject::Properties(false, false));
	this->chestOpen = Node::create();
	this->chestClosed = Node::create();
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->chestPool = nullptr;
	this->isOpen = false;
	this->isLocked = false;
	this->isPlayerColliding = false;

	this->chestOpenArgs = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyArgs, Value("")).asString();

	ChestPoolDeserializer* chestPoolDeserializer = ChestPoolDeserializer::create();

	ValueMap valueMap = ValueMap();

	valueMap[GameObject::MapKeyType] = ChestPoolDeserializer::MapKeyTypeChestPool;
	valueMap[GameObject::MapKeyName] = GameUtils::getKeyOrDefault(this->properties, ChestBase::PropertyRewardPool, Value("")).asString();

	ObjectDeserializer::ObjectDeserializationRequestArgs deserializeArgs = ObjectDeserializer::ObjectDeserializationRequestArgs(valueMap, [=](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		this->chestPool = static_cast<MinMaxPool*>(args.gameObject);
		this->addChild(this->chestPool);
	});

	chestPoolDeserializer->deserialize(&deserializeArgs);

	this->addChild(this->interactCollision);
	this->addChild(this->chestClosed);
	this->addChild(this->chestOpen);
	this->addChild(this->interactMenu);
}

ChestBase::~ChestBase()
{
}

void ChestBase::onEnter()
{
	super::onEnter();

	if (this->getObjectStateOrDefault(ChestBase::SaveKeyIsOpen, Value(false)).asBool())
	{
		this->open();
	}
	else
	{
		this->close();
	}
}

void ChestBase::initializePositions()
{
	super::initializePositions();
}

void ChestBase::initializeListeners()
{
	super::initializeListeners();

	this->interactCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->isPlayerColliding = true;
		this->toggleInteractMenu();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->interactCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->isPlayerColliding = false;
		this->toggleInteractMenu();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_V }, [=](InputEvents::InputArgs* args)
	{
		if (!this->isOpen && !this->isLocked && this->isPlayerColliding)
		{
			this->onInteract();
		}
	});
}

void ChestBase::open()
{
	this->isOpen = true;
	this->chestClosed->setVisible(false);
	this->chestOpen->setVisible(true);

	this->saveObjectState(ChestBase::SaveKeyIsOpen, Value(true));

	this->toggleInteractMenu();
}

void ChestBase::close()
{
	this->isOpen = false;
	this->chestClosed->setVisible(true);
	this->chestOpen->setVisible(false);

	this->saveObjectState(ChestBase::SaveKeyIsOpen, Value(false));

	this->toggleInteractMenu();
}

void ChestBase::onInteract()
{
	this->performUnlockAndGiveItems();
}

void ChestBase::lock()
{
	this->isLocked = true;

	this->toggleInteractMenu();
}

void ChestBase::unlock()
{
	this->isLocked = false;

	this->toggleInteractMenu();
}

void ChestBase::performUnlockAndGiveItems()
{
	this->unlock();
	this->open();

	if (this->chestPool == nullptr)
	{
		this->chestPool = ErrorPool::create();
		this->addChild(this->chestPool);
	}

	PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(this->chestPool, Strings::Platformer_Notifications_ItemFound::create()));
}

void ChestBase::toggleInteractMenu()
{
	if (this->isOpen || this->isLocked || !this->isPlayerColliding)
	{
		this->interactMenu->hide();
	}
	else
	{
		this->interactMenu->show();
	}
}
