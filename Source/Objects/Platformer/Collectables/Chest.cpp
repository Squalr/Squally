#include "Chest.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/Physics//PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string Chest::MapKeyChest = "chest";
const std::string Chest::MapKeyCipherEvent = "open-cipher";

Chest* Chest::create(cocos2d::ValueMap& initProperties)
{
	Chest* instance = new Chest(initProperties);

	instance->autorelease();

	return instance;
}

Chest::Chest(cocos2d::ValueMap& initProperties) : super(initProperties)
{
	this->interactCollision = CollisionObject::create(PhysicsBody::createBox(Size(256.0f, 256.0f)), (CollisionType)PlatformerCollisionType::Collectable, false, false);
	this->chestOpen = Node::create();
	this->chestClosed = Node::create();
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));

	this->chestOpenEvent = GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyEvent, Value("")).asString();
	this->chestOpenArgs = GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyArgs, Value("")).asString();

	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::ChestBaseFront);
	Sprite* chestOpenLidSprite = Sprite::create(ObjectResources::ChestLid);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::ChestClosed);

	this->chestOpen->addChild(chestOpenLidSprite);
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
		this->interactMenu->show();
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->interactCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->interactMenu->hide();
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Chest::update(float dt)
{
	super::update(dt);

	// TODO: Distance check
	if (Input::isKeyJustPressed(EventKeyboard::KeyCode::KEY_V))
	{
		if (this->chestOpenEvent == Chest::MapKeyCipherEvent)
		{
			// TODO: Easy/Hard popup
			CipherEvents::TriggerLoadCipher(CipherEvents::CipherOpenArgs(this->chestOpenArgs, true));
		}
	}
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
