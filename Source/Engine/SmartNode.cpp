#include "SmartNode.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/InputEvents.h"
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
	this->hasInitializedListeners = false;
	this->disposeCallbacks = std::vector<std::function<void()>>();
}

SmartNode::~SmartNode()
{
	for (auto it = this->disposeCallbacks.begin(); it != this->disposeCallbacks.end(); it++)
	{
		(*it)();
	}
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
		this->onDeveloperModeEnable(DeveloperModeController::getInstance()->getDebugLevel());
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		HackableEvents::HackToggleArgs* args = static_cast<HackableEvents::HackToggleArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->onHackerModeEnable(args->hackFlags);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->onHackerModeDisable();
	}));
}

void SmartNode::onDeveloperModeEnable(int debugLevel)
{
}

void SmartNode::onDeveloperModeDisable()
{
}

void SmartNode::onHackerModeEnable(int hackFlags)
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

	wrapper->setTag(listener->getTag());
	wrapper->setIgnorePause(true);

	// Keep the original listener around so that we can invoke it, but disable it
	listener->setEnabled(false);
	listener->setTag("");

	this->addEventListener(wrapper);
	this->addEventListener(listener);
}

static inline unsigned long long TaskId = 0;

void SmartNode::defer(std::function<void()> task)
{
		unsigned long long taskId = TaskId++;
		std::string eventKey = "EVENT_DEFER_TASK_" + std::to_string(taskId);

		// Schedule the task for the next update loop
		this->schedule([=](float dt)
		{
			task();
			this->unschedule(eventKey);
		}, 1.0f / 60.0f, 1, 0.0f, eventKey);
}

EventListener* SmartNode::whenKeyPressed(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	EventListener* listener = EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

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

EventListener* SmartNode::whenKeyPressedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	EventListener* listener = EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

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

EventListener* SmartNode::whenKeyPressedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	EventListener* listener = EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		if (this->hackermodeEnabled)
		{
			InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

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

EventListener* SmartNode::whenKeyReleased(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	EventListener* listener = EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

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

EventListener* SmartNode::whenKeyReleasedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	EventListener* listener = EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

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

EventListener* SmartNode::whenKeyReleasedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	EventListener* listener = EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		if (this->hackermodeEnabled)
		{
			InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

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

void SmartNode::onDispose(std::function<void()> task)
{
	this->disposeCallbacks.push_back(task);
}
