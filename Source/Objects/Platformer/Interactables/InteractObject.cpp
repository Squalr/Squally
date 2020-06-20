#include "InteractObject.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

InteractObject* InteractObject::create(InteractType interactType, Size size, Vec2 offset, Color3B interactColor, Color4F debugColor, bool disableLockDebug)
{
	ValueMap properties = ValueMap();

	InteractObject* instance = new InteractObject(properties, interactType, size, offset, interactColor, debugColor, disableLockDebug);

	instance->autorelease();

	return instance;
}

InteractObject::InteractObject(ValueMap& properties, InteractType interactType, Size size, Vec2 offset, Color3B interactColor, Color4F debugColor, bool disableLockDebug)
	: super(properties)
{
	this->interactType = interactType;
	this->lockButton = disableLockDebug ? nullptr : ClickableNode::create(UIResources::Menus_Icons_Lock, UIResources::Menus_Icons_Lock);
	this->unlockButton = disableLockDebug ? nullptr : ClickableNode::create(UIResources::Menus_Icons_LockUnlocked, UIResources::Menus_Icons_LockUnlocked);
	this->interactCollision = CollisionObject::create(CollisionObject::createBox(size), (CollisionType)PlatformerCollisionType::Trigger, CollisionObject::Properties(false, false), debugColor);
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"), interactColor);
	this->lockedMenu = InteractMenu::create(Strings::Platformer_Objects_Doors_Locked::create(), interactColor);
	this->unlockMenu = InteractMenu::create(Strings::Common_Dash::create()->setStringReplacementVariables(
		{ ConstantString::create("[V]"), Strings::Platformer_Objects_Doors_Unlock::create() }
	), interactColor, 256.0f);
	this->isLocked = !this->listenEvent.empty();
	this->isUnlockable = false;
	this->wasTripped = false;
	this->canInteract = false;
	this->disabled = false;
	this->interactCallback = nullptr;
	this->unlockCallback = nullptr;
	this->squally = nullptr;
	this->scrappy = nullptr;

	this->interactCollision->setName("Interact");

	this->interactCollision->setPosition(offset);
	this->interactMenu->setPosition(offset);
	this->lockedMenu->setPosition(offset);
	this->unlockMenu->setPosition(offset);

	this->addChild(this->interactCollision);
	this->addChild(this->interactMenu);
	this->addChild(this->lockedMenu);
	this->addChild(this->unlockMenu);

	if (!disableLockDebug)
	{
		this->addChild(this->lockButton);
		this->addChild(this->unlockButton);
	}
}

InteractObject::~InteractObject()
{
}

void InteractObject::onEnter()
{
	super::onEnter();

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);
}

void InteractObject::initializePositions()
{
	super::initializePositions();

	if (this->lockButton != nullptr && this->unlockButton != nullptr)
	{
		this->lockButton->setPosition(Vec2(-64.0f, 212.0f));
		this->unlockButton->setPosition(Vec2(64.0f, 212.0f));
	}
}

void InteractObject::initializeListeners()
{
	super::initializeListeners();

	if (this->lockButton != nullptr && this->unlockButton != nullptr)
	{
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
		switch(this->interactType)
		{
			case InteractType::Input:
			{
				// Technically this is bad design in the sense that this object should not need to concern itself with the interacting entity,
				// However in this game only Squally interacts with things via input as of now, so this check is fine.
				if (this->squally != nullptr && this->squally->getRuntimeStateOrDefaultBool(StateKeys::CinematicHijacked, false))
				{
					return;
				}

				this->tryInteractObject();
				break;
			}
			case InteractType::None:
			case InteractType::Collision:
			default:
			{
				break;
			}
		}
	});
}

void InteractObject::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);
	
	if (this->lockButton != nullptr && this->unlockButton != nullptr)
	{
		this->lockButton->setVisible(true);
		this->unlockButton->setVisible(true);
	}
}

void InteractObject::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	if (this->lockButton != nullptr && this->unlockButton != nullptr)
	{
		this->lockButton->setVisible(false);
		this->unlockButton->setVisible(false);
	}
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

	this->updateInteractMenuVisibility();
}

void InteractObject::setInteractCallback(std::function<bool()> interactCallback)
{
	this->interactCallback = interactCallback;
}

void InteractObject::setUnlockable(bool isUnlockable, std::function<bool()> unlockCallback)
{
	this->isUnlockable = isUnlockable;
	this->unlockCallback = unlockCallback;
}

void InteractObject::tryInteractObject()
{
	if (this->canInteract && !this->disabled)
	{
		if (!this->isLocked)
		{
			if (this->interactCallback == nullptr || this->interactCallback())
			{
				this->onInteract();
			}
		}
		else if (this->isUnlockable)
		{
			if (this->unlockCallback == nullptr || this->unlockCallback())
			{
				this->unlock();
			}
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
		this->unlockMenu->hide();
		return;
	}

	if (this->isLocked && this->canInteract)
	{
		if (this->isUnlockable)
		{
			this->unlockMenu->show();
		}
		else
		{
			this->lockedMenu->show();
		}
	}
	else
	{
		this->lockedMenu->hide();
		this->unlockMenu->hide();
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
