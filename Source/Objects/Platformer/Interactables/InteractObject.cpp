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

#include "Strings/Platformer/Objects/Doors/Locked.h"

using namespace cocos2d;

InteractObject::InteractObject(ValueMap& properties, InteractType interactType, Size size, Vec2 offset) : super(properties)
{
	this->interactType = interactType;
	this->interactCollision = CollisionObject::create(PhysicsBody::createBox(size), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->wasTripped = false;
	this->canInteract = false;
	this->disabled = false;
	this->requiresInteraction = true;
	this->interactCallback = nullptr;

	this->interactCollision->setPosition(offset);
	this->interactMenu->setPosition(offset);

	this->addChild(this->interactCollision);
	this->addChild(this->interactMenu);
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
}

void InteractObject::initializeListeners()
{
	super::initializeListeners();

	this->interactCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = true;

		if (!this->requiresInteraction)
		{
			this->tryInteractObject();
		}
		else
		{
			this->updateInteractMenuVisibility();
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});
		 
	this->interactCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = false;
		this->updateInteractMenuVisibility();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_V }, [=](InputEvents::InputArgs* args)
	{
		this->tryInteractObject();
	});
}

void InteractObject::enable()
{
	this->disabled = false;
}

void InteractObject::disable()
{
	this->disabled = true;
}

void InteractObject::setRequiresInteraction(bool requiresInteraction)
{
	this->requiresInteraction = requiresInteraction;
}

void InteractObject::setOpenCallback(std::function<bool()> interactCallback)
{
	this->interactCallback = interactCallback;
}

void InteractObject::tryInteractObject()
{
	if (this->canInteract && !this->disabled)
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

void InteractObject::updateInteractMenuVisibility()
{
	if (!this->requiresInteraction || this->disabled)
	{
		this->interactMenu->hide();
		return;
	}

	if (this->canInteract)
	{
		this->interactMenu->show();
	}
	else
	{
		this->interactMenu->hide();
	}
}
