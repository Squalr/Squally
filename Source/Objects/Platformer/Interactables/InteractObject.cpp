#include "InteractObject.h"

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

#include "Strings/Strings.h"

using namespace cocos2d;

InteractObject* InteractObject::create(InteractType interactType, cocos2d::Size size, cocos2d::Vec2 offset)
{
	ValueMap properties = ValueMap();

	InteractObject* instance = new InteractObject(properties, interactType, size, offset);

	instance->autorelease();

	return instance;
}

InteractObject::InteractObject(ValueMap& properties, InteractType interactType, Size size, Vec2 offset) : super(properties)
{
	this->interactType = interactType;
	this->lockButton = ClickableNode::create(UIResources::Menus_Icons_Lock, UIResources::Menus_Icons_Lock);
	this->unlockButton = ClickableNode::create(UIResources::Menus_Icons_LockUnlocked, UIResources::Menus_Icons_LockUnlocked);
	this->interactCollision = CollisionObject::create(CollisionObject::createBox(size), (CollisionType)PlatformerCollisionType::Trigger, CollisionObject::Properties(false, false));
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->lockedMenu = InteractMenu::create(Strings::Platformer_Objects_Doors_Locked::create());
	this->isLocked = !this->listenEvent.empty();
	this->wasTripped = false;
	this->canInteract = false;
	this->disabled = false;
	this->interactCallback = nullptr;

	this->interactCollision->setPosition(offset);
	this->interactMenu->setPosition(offset);
	this->lockedMenu->setPosition(offset);

	this->addChild(this->interactCollision);
	this->addChild(this->interactMenu);
	this->addChild(this->lockedMenu);
	this->addChild(this->lockButton);
	this->addChild(this->unlockButton);
}

InteractObject::~InteractObject()
{
}

void InteractObject::onEnter()
{
	super::onEnter();
}

void InteractObject::initializePositions()
{
	super::initializePositions();

	this->lockButton->setPosition(Vec2(-64.0f, 212.0f));
	this->unlockButton->setPosition(Vec2(64.0f, 212.0f));
}

void InteractObject::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(this->listenEvent, [=](ValueMap args)
	{
		this->isLocked = false;
		this->updateInteractMenuVisibility();
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

	this->interactCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = true;

		this->onStateRefresh();
		
		return CollisionObject::CollisionResult::DoNothing;
	});
		 
	this->interactCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = false;
		this->updateInteractMenuVisibility();
		this->onEndCollision();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_V }, [=](InputEvents::InputArgs* args)
	{
		this->tryInteractObject();
	});
}

void InteractObject::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);
	
	this->lockButton->setVisible(true);
	this->unlockButton->setVisible(true);
}

void InteractObject::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->lockButton->setVisible(false);
	this->unlockButton->setVisible(false);
}

void InteractObject::onStateRefresh()
{
	switch(this->interactType)
	{
		case InteractType::None:
		{
			break;
		}
		case InteractType::Input:
		{
			this->updateInteractMenuVisibility();
			break;
		}
		case InteractType::Collision:
		{
			this->tryInteractObject();
			break;
		}
	}
}

void InteractObject::enable()
{
	this->disabled = false;

	this->onStateRefresh();
}

void InteractObject::disable()
{
	this->disabled = true;
	
	this->onStateRefresh();
}

void InteractObject::lock(bool animate)
{
	this->isLocked = true;
	this->updateInteractMenuVisibility();
}

void InteractObject::unlock(bool animate)
{
	this->isLocked = false;
	this->updateInteractMenuVisibility();

	this->broadcastMapEvent(this->sendEvent, ValueMap());
}

void InteractObject::setInteractType(InteractType interactType)
{
	this->interactType = interactType;
}

void InteractObject::setOpenCallback(std::function<bool()> interactCallback)
{
	this->interactCallback = interactCallback;
}

void InteractObject::tryInteractObject()
{
	if (!this->isLocked && this->canInteract && !this->disabled)
	{
		if (this->interactCallback == nullptr || this->interactCallback())
		{
			this->onInteract();
		}
	}
}

void InteractObject::onInteract()
{
}

void InteractObject::onEndCollision()
{
}

void InteractObject::updateInteractMenuVisibility()
{
	if (this->interactType != InteractType::Input || this->disabled)
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
