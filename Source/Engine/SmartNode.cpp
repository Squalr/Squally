#include "SmartNode.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SmartNode* SmartNode::create()
{
	SmartNode* instance = new SmartNode();

	instance->autorelease();

	return instance;
}

SmartNode::SmartNode()
{
	this->hackermodeEnabled = false;
	this->optimizationHasGlobalListener = false;
	this->optimizationHasListener = false;
}

SmartNode::~SmartNode()
{
}

void SmartNode::onEnter()
{
	super::onEnter();

	this->initializePositions();
	this->initializeListeners();

	if (this->isDeveloperModeEnabled())
	{
		this->onDeveloperModeEnable();
	}
	else
	{
		this->onDeveloperModeDisable();
	}
}

void SmartNode::onExit()
{
	super::onExit();

	// Only attempt to remove non global listeners if we've ever added one. Optimization to save significant time.
	if (this->optimizationHasGlobalListener)
	{
		this->removeNonGlobalListeners();
	}
}

void SmartNode::onReenter()
{
	super::onReenter();

	this->initializePositions();
	this->initializeListeners();
}

void SmartNode::initializePositions()
{
}

void SmartNode::initializeListeners()
{
	// Only attempt to remove listeners if we've ever added one. Optimization to save significant time.
	if (this->optimizationHasListener)
	{
		this->removeAllListeners();
	}

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventQueryObject, [=](EventCustom* eventCustom)
	{
		QueryObjectsArgsBase* args = static_cast<QueryObjectsArgsBase*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			args->tryInvoke(this);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::EventDeveloperModeModeEnable, [=](EventCustom* args)
	{
		this->onDeveloperModeEnable();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::EventDeveloperModeModeDisable, [=](EventCustom* args)
	{
		this->onDeveloperModeDisable();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		HackableEvents::HackToggleArgs* args = static_cast<HackableEvents::HackToggleArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->onHackerModeEnable(args->currentEq);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->onHackerModeDisable();
	}));
}

void SmartNode::onDeveloperModeEnable()
{
}

void SmartNode::onDeveloperModeDisable()
{
}

void SmartNode::onHackerModeEnable(int eq)
{
	this->hackermodeEnabled = true;
}

void SmartNode::onHackerModeDisable()
{
	this->hackermodeEnabled = false;
}

bool SmartNode::isDeveloperModeEnabled()
{
	return DeveloperModeController::getInstance()->isDeveloperModeEnabled();
}

void SmartNode::removeAllListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void SmartNode::removeNonGlobalListeners()
{
	this->getEventDispatcher()->removeEventListenersForTargetWhere(this, [=](EventListener* listener)
	{
		return !listener->isGlobal();
	});
}

void SmartNode::addEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	if (!listener->isGlobal())
	{
		this->optimizationHasGlobalListener = true;
	}

	this->optimizationHasListener = true;

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SmartNode::removeEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->removeEventListener(listener);
}

void SmartNode::addEventListenerIgnorePause(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	EventListenerCustom* wrapper = EventListenerCustom::create(listener->getListenerId(), [=](EventCustom* eventCustom)
	{
		if (GameUtils::isInRunningScene(this))
		{
			listener->invoke(eventCustom);
		}
	});

	wrapper->setIgnorePause(true);

	// Keep the original listener around so that we can invoke it, but disable it
	listener->setEnabled(false);

	this->addEventListener(wrapper);
	this->addEventListener(listener);
}

void SmartNode::whenKeyPressed(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListener(EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->handled && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	}));
}

void SmartNode::whenKeyPressedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->handled && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	}));
}

void SmartNode::whenKeyPressedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		if (this->hackermodeEnabled)
		{
			InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

			if (args != nullptr && !args->handled && keyCodes.find(args->keycode) != keyCodes.end())
			{
				if (!requireVisible || GameUtils::isVisible(this))
				{
					callback(args);
				}
			}
		}
	}));
}

void SmartNode::whenKeyReleased(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListener(EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->handled && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	}));
}

void SmartNode::whenKeyReleasedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->handled && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	}));
}

void SmartNode::whenKeyReleasedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		if (this->hackermodeEnabled)
		{
			InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

			if (args != nullptr && !args->handled && keyCodes.find(args->keycode) != keyCodes.end())
			{
				if (!requireVisible || GameUtils::isVisible(this))
				{
					callback(args);
				}
			}
		}
	}));
}
