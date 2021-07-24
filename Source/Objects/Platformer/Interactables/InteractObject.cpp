#include "InteractObject.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
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

InteractObject* InteractObject::create(
	InteractType interactType,
	Size size,
	Vec2 offset,
	LocalizedString* actionStr,
	InputEvents::KeyCode input,
	Color3B interactColor,
	Color4F debugColor,
	bool disableLockDebug)
{
	ValueMap properties = ValueMap();

	InteractObject* instance = new InteractObject(properties, interactType, size, offset, actionStr, input, interactColor, debugColor, disableLockDebug);

	instance->autorelease();

	return instance;
}

InteractObject::InteractObject(
	ValueMap& properties,
	InteractType interactType,
	Size size,
	Vec2 offset,
	LocalizedString* actionStr,
	InputEvents::KeyCode input,
	Color3B interactColor,
	Color4F debugColor,
	bool disableLockDebug)
	: super(properties)
{
	this->input = input;
	this->interactType = interactType;
	this->lockButton = disableLockDebug ? nullptr : ClickableNode::create(UIResources::Menus_Icons_Lock, UIResources::Menus_Icons_Lock);
	this->unlockButton = disableLockDebug ? nullptr : ClickableNode::create(UIResources::Menus_Icons_LockUnlocked, UIResources::Menus_Icons_LockUnlocked);
	this->contentNode = Node::create();
	this->interactCollision = CollisionObject::create(CollisionObject::createBox(size), (CollisionType)PlatformerCollisionType::Trigger, CollisionObject::Properties(false, false), debugColor);

	if (actionStr == nullptr)
	{
		this->interactKeyStr = ConstantString::create(this->inputToString(this->input));
	}
	else
	{
		this->interactKeyStr = Strings::Common_Dash::create()->setStringReplacementVariables(
			{ ConstantString::create(this->inputToString(this->input)), actionStr });
	}
	
	this->unlockKeyStr = ConstantString::create(this->inputToString(this->input));
	this->interactMenu = LazyNode<InteractMenu>::create([=](){ return InteractMenu::create(this->interactKeyStr, interactColor, offset); });
	this->lockedMenu = LazyNode<InteractMenu>::create([=](){ return InteractMenu::create(Strings::Platformer_Objects_Doors_Locked::create(), interactColor, offset); });
	this->unlockMenu = LazyNode<InteractMenu>::create([=](){ return InteractMenu::create(Strings::Common_Dash::create()->setStringReplacementVariables(
		{ this->unlockKeyStr, Strings::Platformer_Objects_Doors_Unlock::create() }), interactColor, offset, 256.0f); });

	// These are potentially passed to the interact menu as captured lambda later, we need to hold onto a ref
	this->unlockKeyStr->retain();
	this->interactKeyStr->retain();

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

	this->addChild(this->contentNode);
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
	this->unlockKeyStr->release();
	this->interactKeyStr->release();
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

	this->interactCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Hover }, [=](CollisionData data)
	{
		this->canInteract = true;

		this->onStateRefresh();
		
		return CollisionResult::DoNothing;
	});
		 
	this->interactCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Hover }, [=](CollisionData data)
	{
		if (!this->interactCollision->isCollidingWithType((int)PlatformerCollisionType::Player)
			&& !this->interactCollision->isCollidingWithType((int)PlatformerCollisionType::Hover))
		{
			this->canInteract = false;
			this->updateInteractMenuVisibility();
			this->onEndCollision();
		}

		return CollisionResult::DoNothing;
	});

	this->whenKeyPressed({ this->input }, [=](InputEvents::KeyboardEventArgs* args)
	{
		switch(this->interactType)
		{
			case InteractType::Input:
			{
				// Technically this is bad design in the sense that we hard code squally, but it seems like this game is unlikely to support
				// Non-squally entities interacting with objects.
				this->tryInteractObject(this->squally);
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
			this->tryInteractObject(this->squally);
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

	this->onStateRefresh();
}

bool InteractObject::isInteractable() const
{
	return this->interactType == InteractType::Input;
}

bool InteractObject::getIsLocked() const
{
	return this->isLocked;
}

bool InteractObject::getIsDisabled() const
{
	return this->disabled;
}

void InteractObject::tryInteractObject(PlatformerEntity* interactingEntity)
{
	if (interactingEntity == nullptr || interactingEntity->getRuntimeStateOrDefaultBool(StateKeys::CinematicHijacked, false))
	{
		return;
	}

	if (this->canInteract && !this->disabled)
	{
		if (!this->isLocked)
		{
			if (this->interactCallback == nullptr || this->interactCallback())
			{
				this->onInteract(interactingEntity);
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

void InteractObject::onInteract(PlatformerEntity* interactingEntity)
{
}

void InteractObject::onEndCollision()
{
}

void InteractObject::updateInteractMenuVisibility()
{
	if (this->interactType != InteractType::Input || this->disabled)
	{
		if (this->interactMenu->isBuilt())
		{
			this->interactMenu->lazyGet()->hide();
		}

		if (this->lockedMenu->isBuilt())
		{
			this->lockedMenu->lazyGet()->hide();
		}

		if (this->unlockMenu->isBuilt())
		{
			this->unlockMenu->lazyGet()->hide();
		}
		return;
	}

	if (this->isLocked && this->canInteract)
	{
		if (this->isUnlockable)
		{
			this->unlockMenu->lazyGet()->show();
			this->lockedMenu->lazyGet()->hide();
		}
		else
		{
			this->unlockMenu->lazyGet()->hide();
			this->lockedMenu->lazyGet()->show();
		}
	}
	else
	{
		if (this->lockedMenu->isBuilt())
		{
			this->lockedMenu->lazyGet()->hide();
		}

		if (this->unlockMenu->isBuilt())
		{
			this->unlockMenu->lazyGet()->hide();
		}
	}

	if (!this->isLocked && this->canInteract)
	{
		this->interactMenu->lazyGet()->show();
	}
	else
	{
		if (this->interactMenu->isBuilt())
		{
			this->interactMenu->lazyGet()->hide();
		}
	}
}

std::string InteractObject::inputToString(InputEvents::KeyCode input)
{
	std::string inputStr = "";

	switch(input)
	{
        case InputEvents::KeyCode::KEY_A: { inputStr = "A"; break; }
        case InputEvents::KeyCode::KEY_B: { inputStr = "B"; break; }
        case InputEvents::KeyCode::KEY_C: { inputStr = "C"; break; }
        case InputEvents::KeyCode::KEY_D: { inputStr = "D"; break; }
        case InputEvents::KeyCode::KEY_E: { inputStr = "E"; break; }
        case InputEvents::KeyCode::KEY_F: { inputStr = "F"; break; }
        case InputEvents::KeyCode::KEY_G: { inputStr = "G"; break; }
        case InputEvents::KeyCode::KEY_H: { inputStr = "H"; break; }
        case InputEvents::KeyCode::KEY_I: { inputStr = "I"; break; }
        case InputEvents::KeyCode::KEY_J: { inputStr = "J"; break; }
        case InputEvents::KeyCode::KEY_K: { inputStr = "K"; break; }
        case InputEvents::KeyCode::KEY_L: { inputStr = "L"; break; }
        case InputEvents::KeyCode::KEY_M: { inputStr = "M"; break; }
        case InputEvents::KeyCode::KEY_N: { inputStr = "N"; break; }
        case InputEvents::KeyCode::KEY_O: { inputStr = "O"; break; }
        case InputEvents::KeyCode::KEY_P: { inputStr = "P"; break; }
        case InputEvents::KeyCode::KEY_Q: { inputStr = "Q"; break; }
        case InputEvents::KeyCode::KEY_R: { inputStr = "R"; break; }
        case InputEvents::KeyCode::KEY_S: { inputStr = "S"; break; }
        case InputEvents::KeyCode::KEY_T: { inputStr = "T"; break; }
        case InputEvents::KeyCode::KEY_U: { inputStr = "U"; break; }
        case InputEvents::KeyCode::KEY_V: { inputStr = "V"; break; }
        case InputEvents::KeyCode::KEY_W: { inputStr = "W"; break; }
        case InputEvents::KeyCode::KEY_X: { inputStr = "X"; break; }
        case InputEvents::KeyCode::KEY_Y: { inputStr = "Y"; break; }
        case InputEvents::KeyCode::KEY_Z: { inputStr = "Z"; break; }
		default:
		{
			inputStr = "UNMAPPED";
		}
	}

	return "[" + inputStr + "]";
}
