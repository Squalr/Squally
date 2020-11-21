#include "SmartNode.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

unsigned long long SmartNode::TaskId = 0;

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
	this->hasInitializedListeners = false;
	this->disableHackerModeEvents = false;
}

SmartNode::~SmartNode()
{
}

void SmartNode::onEnter()
{
	super::onEnter();

	this->initializePositions();

	if (!this->hasInitializedListeners)
	{
		this->initializeListeners();
		this->hasInitializedListeners = true;
	}

	if (this->isDeveloperModeEnabled())
	{
		this->onDeveloperModeEnable(DeveloperModeController::getDebugLevel());
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

	// Only listen for dev events in non-dev builds to save time in release mode
	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::EventDeveloperModeModeEnable, [=](EventCustom* eventCustom)
		{
			DeveloperModeEvents::DeveloperModeEnableArgs* args = static_cast<DeveloperModeEvents::DeveloperModeEnableArgs*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				this->onDeveloperModeEnable(args->debugLevel);
			}
		}));

		this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::EventDeveloperModeModeDisable, [=](EventCustom* eventCustom)
		{
			this->onDeveloperModeDisable();
		}));
	}

	if (!this->disableHackerModeEvents)
	{
		this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
		{
			HackToggleArgs* args = static_cast<HackToggleArgs*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				this->onHackerModeEnable();
			}
		}));

		this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
		{
			this->onHackerModeDisable();
		}));
	}
}

void SmartNode::onDeveloperModeEnable(int debugLevel)
{
}

void SmartNode::onDeveloperModeDisable()
{
}

void SmartNode::onHackerModeEnable()
{
	this->hackermodeEnabled = true;
}

void SmartNode::onHackerModeDisable()
{
	this->hackermodeEnabled = false;
}

bool SmartNode::isDeveloperModeEnabled()
{
	return DeveloperModeController::isDeveloperModeEnabled();
}

void SmartNode::removeAllListeners()
{
	this->optimizationHasGlobalListener = false;
	this->optimizationHasListener = false;
	this->hasInitializedListeners = false;
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void SmartNode::removeNonGlobalListeners()
{
	this->hasInitializedListeners = false;
	this->getEventDispatcher()->removeEventListenersForTargetWhere(this, [=](EventListener* listener)
	{
		return !listener->isGlobal();
	});
}

void SmartNode::addEventListener(EventListenerCustom* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	if (listener->isGlobal())
	{
		this->optimizationHasGlobalListener = true;
	}

	this->optimizationHasListener = true;

	this->getEventDispatcher()->addEventListener(listener);
}

void SmartNode::removeEventListener(EventListenerCustom* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->removeEventListener(listener);
}

void SmartNode::addEventListenerIgnorePause(EventListenerCustom* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	EventListenerCustom* wrapper = EventListenerCustom::create(listener->getListenerId(), [=](EventCustom* eventCustom)
	{
		if (listener->isGlobal() || GameUtils::isInRunningScene(this))
		{
			listener->invoke(eventCustom);
		}
	});

	wrapper->setTag(listener->getTag());
	wrapper->setIgnorePause(true);

	// Keep the original listener around so that we can invoke it, but disable it
	listener->setEnabled(false);
	listener->setTag("");

	this->addEventListener(wrapper);
	this->addEventListener(listener);
}

void SmartNode::addGlobalEventListener(EventListenerCustom* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIsGlobal(true);

	this->addEventListenerIgnorePause(listener);
}

void SmartNode::removeEventListenerByTag(std::string tag)
{
	if (tag.empty())
	{
		return;
	}

	this->getEventDispatcher()->removeEventListenersForTargetWhere(this, [=](EventListener* listener)
	{
		return listener->getTag() == tag;
	});
}

void SmartNode::defer(std::function<void()> task, int ticks)
{
	unsigned long long taskId = SmartNode::TaskId++;
	std::string eventKey = "EVENT_DEFER_TASK_" + std::to_string(taskId);

	// Schedule the task for the next update loop
	this->schedule([=](float dt)
	{
		if (ticks <= 1)
		{
			task();
		}
		else
		{
			this->defer(task, ticks - 1);
		}

		this->unschedule(eventKey);
	}, eventKey, 0.0f, 1);
}

void SmartNode::scheduleEvery(std::function<void()> task, float seconds)
{
	unsigned long long taskId = SmartNode::TaskId++;
	std::string eventKey = "EVENT_DEFER_TASK_" + std::to_string(taskId);

	// Schedules the task to be repeated every x seconds.
	this->schedule([=](float dt)
	{
		task();
	}, eventKey, seconds);
}

EventListenerCustom* SmartNode::whenKeyPressed(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(InputEvents::KeyboardEventArgs*)> callback, bool requireVisible)
{
	EventListenerCustom* listener = EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	});

	this->addEventListener(listener);

	return listener;
}

EventListenerCustom* SmartNode::whenKeyPressedIgnorePause(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(InputEvents::KeyboardEventArgs*)> callback, bool requireVisible)
{
	EventListenerCustom* listener = EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	});

	this->addEventListenerIgnorePause(listener);

	return listener;
}

EventListenerCustom* SmartNode::whenKeyPressedHackerMode(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(InputEvents::KeyboardEventArgs*)> callback, bool requireVisible)
{
	EventListenerCustom* listener = EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		if (this->hackermodeEnabled)
		{
			InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getUserData());

			if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
			{
				if (!requireVisible || GameUtils::isVisible(this))
				{
					callback(args);
				}
			}
		}
	});

	this->addEventListenerIgnorePause(listener);

	return listener;
}

EventListenerCustom* SmartNode::whenKeyReleased(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(InputEvents::KeyboardEventArgs*)> callback, bool requireVisible)
{
	EventListenerCustom* listener = EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	});

	this->addEventListener(listener);

	return listener;
}

EventListenerCustom* SmartNode::whenKeyReleasedIgnorePause(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(InputEvents::KeyboardEventArgs*)> callback, bool requireVisible)
{
	EventListenerCustom* listener = EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	});

	this->addEventListenerIgnorePause(listener);

	return listener;
}

EventListenerCustom* SmartNode::whenKeyReleasedHackerMode(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(InputEvents::KeyboardEventArgs*)> callback, bool requireVisible)
{
	EventListenerCustom* listener = EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		if (this->hackermodeEnabled)
		{
			InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getUserData());

			if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
			{
				if (!requireVisible || GameUtils::isVisible(this))
				{
					callback(args);
				}
			}
		}
	});

	this->addEventListenerIgnorePause(listener);

	return listener;
}

EventListenerCustom* SmartNode::whenScrollUp(std::function<void(InputEvents::MouseEventArgs*)> callback, bool requireVisible)
{
	EventListenerCustom* listener = EventListenerCustom::create(InputEvents::EventMouseScroll, [=](EventCustom* eventCustom)
	{
		InputEvents::MouseEventArgs* args = static_cast<InputEvents::MouseEventArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && args->scrollDelta.y < 0.0f)
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	});

	this->addEventListener(listener);

	return listener;
}

EventListenerCustom* SmartNode::whenScrollDown(std::function<void(InputEvents::MouseEventArgs*)> callback, bool requireVisible)
{
	EventListenerCustom* listener = EventListenerCustom::create(InputEvents::EventMouseScroll, [=](EventCustom* eventCustom)
	{
		InputEvents::MouseEventArgs* args = static_cast<InputEvents::MouseEventArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && args->scrollDelta.y > 0.0f)
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	});

	this->addEventListener(listener);

	return listener;
}
