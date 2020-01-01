#include "SmartScene.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"

const float SmartScene::defaultFadeSpeed = 0.75f;
unsigned long long SmartScene::TaskId = 0;

using namespace cocos2d;

SmartScene* SmartScene::create()
{
	SmartScene* instance = new SmartScene();

	instance->autorelease();

	return instance;
}

SmartScene::SmartScene()
{
	this->hackermodeEnabled = false;
	this->fadeAction = nullptr;
	this->fadeSpeed = SmartScene::defaultFadeSpeed;
	this->layerColorHud = Hud::create();
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 255));
	this->disposeCallbacks = std::vector<std::function<void()>>();

	this->layerColor->setContentSize(Director::getInstance()->getVisibleSize());

	this->layerColorHud->setLocalZOrder(99999);

	this->layerColorHud->addChild(this->layerColor);
	this->addChild(this->layerColorHud);
}

SmartScene::~SmartScene()
{
	for (auto it = this->disposeCallbacks.begin(); it != this->disposeCallbacks.end(); it++)
	{
		(*it)();
	}
}

void SmartScene::onEnter()
{
	super::onEnter();

	// Make fade in visible, fullscreen, and topmost
	if (this->fadeSpeed > 0.0f)
	{
		this->layerColor->setOpacity(255);

		// Fade into the scene
		this->fadeAction = FadeOut::create(this->fadeSpeed);
		this->layerColor->runAction(this->fadeAction);
	}
	else
	{
		this->layerColor->setOpacity(0);
	}

	this->initializePositions();
	this->initializeListeners();

	if (this->isDeveloperModeEnabled())
	{
		this->onDeveloperModeEnable(DeveloperModeController::getDebugLevel());
	}
	else
	{
		this->onDeveloperModeDisable();
	}
}

void SmartScene::onExit()
{
	super::onExit();

	this->removeNonGlobalListeners();
}

void SmartScene::initializePositions()
{
}

void SmartScene::initializeListeners()
{
	this->removeAllListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(DeveloperModeEvents::EventDeveloperModeModeEnable, [=](EventCustom* args)
	{
		this->onDeveloperModeEnable(DeveloperModeController::getDebugLevel());
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
			this->onHackerModeEnable(args->hackFlags);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->onHackerModeDisable();
	}));
}

void SmartScene::onDeveloperModeEnable(int debugLevel)
{
}

void SmartScene::onDeveloperModeDisable()
{
}

void SmartScene::onHackerModeEnable(int hackFlags)
{
	this->hackermodeEnabled = true;
}

void SmartScene::onHackerModeDisable()
{
	this->hackermodeEnabled = false;
}

bool SmartScene::isDeveloperModeEnabled()
{
	return DeveloperModeController::isDeveloperModeEnabled();
}

void SmartScene::removeAllListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void SmartScene::removeNonGlobalListeners()
{
	this->getEventDispatcher()->removeEventListenersForTargetWhere(this, [=](EventListener* listener)
	{
		return !listener->isGlobal();
	});
}

void SmartScene::addEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SmartScene::removeEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	this->getEventDispatcher()->removeEventListener(listener);
}

void SmartScene::addEventListenerIgnorePause(EventListener* listener)
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

void SmartScene::setFadeSpeed(float newFadeSpeed)
{
	this->fadeSpeed = newFadeSpeed;
}

float SmartScene::getFadeSpeed()
{
	return this->fadeSpeed;
}

void SmartScene::pause()
{
	// On pause cancel the fade in animation
	if (this->fadeAction != nullptr)
	{
		this->stopAction(this->fadeAction);
		this->layerColor->setOpacity(0);
	}

	super::pause();
}

void SmartScene::defer(std::function<void()> task)
{
		unsigned long long taskId = SmartScene::TaskId++;
		std::string eventKey = "EVENT_SCENE_DEFER_TASK_" + std::to_string(taskId);

		// Schedule the task for the next update loop
		this->schedule([=](float dt)
		{
			task();
			this->unschedule(eventKey);
		}, 1.0f / 60.0f, 1, 0.0f, eventKey);
}

void SmartScene::whenKeyPressed(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListener(EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	}));
}

void SmartScene::whenKeyPressedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	}));
}

void SmartScene::whenKeyPressedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(InputEvents::EventKeyJustPressed, [=](EventCustom* eventCustom)
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
	}));
}

void SmartScene::whenKeyReleased(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListener(EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	}));
}

void SmartScene::whenKeyReleasedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
	{
		InputEvents::InputArgs* args = static_cast<InputEvents::InputArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled() && keyCodes.find(args->keycode) != keyCodes.end())
		{
			if (!requireVisible || GameUtils::isVisible(this))
			{
				callback(args);
			}
		}
	}));
}

void SmartScene::whenKeyReleasedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(InputEvents::EventKeyJustReleased, [=](EventCustom* eventCustom)
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
	}));
}

void SmartScene::onDispose(std::function<void()> task)
{
	this->disposeCallbacks.push_back(task);
}
