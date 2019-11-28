#include "Portal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Platformer/Objects/Doors/Locked.h"

using namespace cocos2d;

const std::string Portal::MapKeyPortal = "portal";
const std::string Portal::MapKeyPortalTransition = "transition";
const std::string Portal::MapKeyPortalMap = "map";

Portal* Portal::create(ValueMap& properties)
{
	Portal* instance = new Portal(properties, Size(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()));

	instance->autorelease();

	return instance;
}

Portal::Portal(ValueMap& properties, Size size, Vec2 offset) : super(properties)
{
	this->portalCollision = CollisionObject::create(PhysicsBody::createBox(size), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->lockButton = ClickableNode::create(UIResources::Menus_Icons_Lock, UIResources::Menus_Icons_Lock);
	this->unlockButton = ClickableNode::create(UIResources::Menus_Icons_LockUnlocked, UIResources::Menus_Icons_LockUnlocked);
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->lockedMenu = InteractMenu::create(Strings::Platformer_Objects_Doors_Locked::create());
	this->wasTripped = false;
	this->canInteract = false;
	this->disabled = false;
	this->mapFile = GameUtils::getKeyOrDefault(this->properties, Portal::MapKeyPortalMap, Value("")).asString();
	this->isLocked = !this->listenEvent.empty();
	this->requiresInteraction = true;
	this->transition = GameUtils::getKeyOrDefault(this->properties, Portal::MapKeyPortalTransition, Value("")).asString();
	this->openCallback = nullptr;

	this->portalCollision->setPosition(offset);
	this->interactMenu->setPosition(offset);
	this->lockedMenu->setPosition(offset);

	this->addChild(this->portalCollision);
	this->addChild(this->lockButton);
	this->addChild(this->unlockButton);
	this->addChild(this->interactMenu);
	this->addChild(this->lockedMenu);
}

Portal::~Portal()
{
}

void Portal::onEnter()
{
	super::onEnter();
}

void Portal::initializePositions()
{
	super::initializePositions();

	this->lockButton->setPosition(Vec2(-64.0f, 212.0f));
	this->unlockButton->setPosition(Vec2(64.0f, 212.0f));
}

void Portal::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(this->listenEvent, [=](ValueMap args)
	{
		this->isLocked = false;
		this->updateInteractMenuVisibility();
	});
 
	this->portalCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = true;

		if (!this->isLocked && !this->requiresInteraction)
		{
			this->loadMap();
		}
		else
		{
			this->updateInteractMenuVisibility();
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});
		 
	this->portalCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = false;
		this->updateInteractMenuVisibility();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_V }, [=](InputEvents::InputArgs* args)
	{
		this->enterPortal();
	});

	this->lockButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->lock(false);
		this->updateInteractMenuVisibility();
	});

	this->unlockButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->unlock(false);
		this->enable();
		this->updateInteractMenuVisibility();
	});
}

void Portal::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();
	
	this->lockButton->setVisible(true);
	this->unlockButton->setVisible(true);
}

void Portal::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->lockButton->setVisible(false);
	this->unlockButton->setVisible(false);
}

void Portal::enable()
{
	this->disabled = false;
}

void Portal::disable()
{
	this->disabled = true;
}

void Portal::lock(bool animate)
{
	this->isLocked = true;
	this->updateInteractMenuVisibility();
}

void Portal::unlock(bool animate)
{
	this->isLocked = false;
	this->updateInteractMenuVisibility();

	this->broadcastMapEvent(this->sendEvent, ValueMap());
}

void Portal::setRequiresInteraction(bool requiresInteraction)
{
	this->requiresInteraction = requiresInteraction;
}

void Portal::setOpenCallback(std::function<bool()> openCallback)
{
	this->openCallback = openCallback;
}

void Portal::enterPortal()
{
	if (!this->isLocked && this->canInteract && !this->disabled)
	{
		if (this->openCallback == nullptr || this->openCallback())
		{
			this->loadMap();
		}
	}
}

void Portal::loadMap()
{
	if (this->disabled || this->mapFile.empty() || this->wasTripped)
	{
		return;
	}

	this->wasTripped = true;

	// Load new map after a short delay -- changing scenes in the middle of a collision causes a crash
	// (not sure why, changing to a combat map is fine)
	this->runAction(Sequence::create(
		DelayTime::create(0.1f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerBeforePlatformerMapChange();
			PlatformerMap* map = PlatformerMap::create("Public/Platformer/Maps/" + this->mapFile + ".tmx", this->transition);
			NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(map));
		}),
		nullptr
	));
}

void Portal::updateInteractMenuVisibility()
{
	if (!this->requiresInteraction || this->disabled)
	{
		this->interactMenu->hide();
		this->lockedMenu->hide();
		return;
	}

	if (this->isLocked && this->canInteract)
	{
		this->lockedMenu->show();
	}
	else
	{
		this->lockedMenu->hide();
	}

	if (!this->isLocked && this->canInteract)
	{
		this->interactMenu->show();
	}
	else
	{
		this->interactMenu->hide();
	}
}
