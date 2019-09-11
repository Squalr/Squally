#include "Chest.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/Physics//PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

Chest::Chest(cocos2d::ValueMap& properties) : super(properties)
{
	this->interactCollision = CollisionObject::create(PhysicsBody::createBox(Size(256.0f, 256.0f)), (CollisionType)PlatformerCollisionType::Collectable, false, false);
	this->chestOpen = Node::create();
	this->chestClosed = Node::create();
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->isLocked = false;
	this->isPlayerColliding = false;

	this->chestOpenArgs = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyArgs, Value("")).asString();

	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Collectables_Chests_ChestOpen);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Collectables_Chests_ChestClosed);

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);

	this->close();

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

	this->scheduleUpdate();
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
		if (!this->isLocked && this->isPlayerColliding)
		{
			this->onInteract();
		}
	});
}

void Chest::open()
{
	this->chestClosed->setVisible(false);
	this->chestOpen->setVisible(true);
}

void Chest::close()
{
	this->chestClosed->setVisible(true);
	this->chestOpen->setVisible(false);
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
	if (this->isLocked || !this->isPlayerColliding)
	{
		this->interactMenu->hide();
	}
	else
	{
		this->interactMenu->show();
	}
}
