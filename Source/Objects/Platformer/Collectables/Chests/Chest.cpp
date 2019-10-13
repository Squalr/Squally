#include "Chest.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Objects/Platformer/Collectables/Chests/ChestPools/ChestPoolDeserializer.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Chest::MapKeyPropertyRewardPool = "reward-pool";
const std::string Chest::SaveKeyIsOpen = "SAVE_KEY_IS_OPEN";

Chest::Chest(cocos2d::ValueMap& properties) : super(properties)
{
	this->interactCollision = CollisionObject::create(PhysicsBody::createBox(Size(128.0f, 96.0f)), (CollisionType)PlatformerCollisionType::Collectable, false, false);
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
	valueMap[GameObject::MapKeyName] = GameUtils::getKeyOrDefault(this->properties, Chest::MapKeyPropertyRewardPool, Value("")).asString();

	ObjectDeserializer::ObjectDeserializationRequestArgs deserializeArgs = ObjectDeserializer::ObjectDeserializationRequestArgs(valueMap, [=](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		this->chestPool = static_cast<MinMaxPool*>(args.gameObject);
		this->addChild(this->chestPool);
	});

	chestPoolDeserializer->deserialize(&deserializeArgs);

	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Collectables_Chests_ChestOpen);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Collectables_Chests_ChestClosed);

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);

	this->addChild(this->interactCollision);
	this->addChild(this->chestClosed);
	this->addChild(this->chestOpen);
	this->addChild(this->interactMenu);
}

Chest::~Chest()
{
}

void Chest::onEnter()
{
	super::onEnter();

	if (this->getObjectStateOrDefault(Chest::SaveKeyIsOpen, Value(false)).asBool())
	{
		this->open();
	}
	else
	{
		this->close();
	}
}

void Chest::initializePositions()
{
	super::initializePositions();
}

void Chest::initializeListeners()
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

void Chest::open()
{
	this->isOpen = true;
	this->chestClosed->setVisible(false);
	this->chestOpen->setVisible(true);

	this->saveObjectState(Chest::SaveKeyIsOpen, Value(true));

	this->toggleInteractMenu();
}

void Chest::close()
{
	this->isOpen = false;
	this->chestClosed->setVisible(true);
	this->chestOpen->setVisible(false);

	this->saveObjectState(Chest::SaveKeyIsOpen, Value(false));

	this->toggleInteractMenu();
}

void Chest::lock()
{
	this->isLocked = true;

	this->toggleInteractMenu();
}

void Chest::unlock()
{
	this->isLocked = false;

	this->toggleInteractMenu();
}

void Chest::toggleInteractMenu()
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
