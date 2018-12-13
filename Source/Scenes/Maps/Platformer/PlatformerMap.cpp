#include "PlatformerMap.h"

PlatformerMap* PlatformerMap::instance = nullptr;
bool PlatformerMap::hackerMode = false;
bool PlatformerMap::developerMode = false;

void PlatformerMap::registerGlobalScene()
{
	if (PlatformerMap::instance == nullptr)
	{
		PlatformerMap::instance = new PlatformerMap();
		PlatformerMap::instance->autorelease();
		PlatformerMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(PlatformerMap::instance);
}

PlatformerMap::PlatformerMap()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (!IMap::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -768.0f));

	this->map = nullptr;
	this->hackerModeBackground = Sprite::create(BackgroundResources::MatrixRain_HackerModeBackground);
	this->hackerModeRain = MatrixRain::create();
	this->hud = Hud::create();
	this->developerHud = DeveloperHud::create();
	this->hackerModeHud = HackerModeHud::create(CC_CALLBACK_0(PlatformerMap::toggleHackerMode, this));
	this->mapNode = Node::create();
	this->mouseLayer = Node::create();
	this->pauseMenu = PauseMenu::create();
	this->optionsMenu = OptionsMenu::create();
	this->confirmationMenu = ConfirmationMenu::create();
	this->menuBackDrop = Hud::create();

	this->menuBackDrop->addChild(LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height));

	this->hackerModeBackground->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->hackerModeBackground->setVisible(false);
	this->hackerModeRain->setVisible(false);
	this->hackerModeHud->setVisible(false);
	this->developerHud->setVisible(false);

	this->addChild(this->hackerModeBackground);
	this->addChild(this->hackerModeRain);
	this->addChild(this->mapNode);
	this->addChild(this->hud);
	this->addChild(this->developerHud);
	this->addChild(this->hackerModeHud);
	this->addChild(this->menuBackDrop);
	this->addChild(this->pauseMenu);
	this->addChild(this->optionsMenu);
	this->addChild(this->confirmationMenu);
	this->mouseLayer->addChild(Mouse::create());
	this->addChild(this->mouseLayer);
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	IMap::onEnter();

	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(false);
	this->confirmationMenu->setVisible(false);

	GameCamera::getInstance()->setScrollOffset(Vec2(64.0f, 32.0f));
	GameCamera::getInstance()->setFollowSpeed(Vec2(0.075f, 0.075f));

	this->scheduleUpdate();

	//GameCamera::getInstance()->setTrackOffset(Vec2(0.0f, 128.0f));
	//GameCamera::getInstance()->pushTarget(Squally::getInstance());
	GameCamera::getInstance()->setTarget(Squally::getInstance(), Vec2(0.0f, 128.0f));
}

void PlatformerMap::initializePositions()
{
	IMap::initializePositions();
}

void PlatformerMap::initializeListeners()
{
	IMap::initializeListeners();

	PlatformerMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateMap, [](EventCustom* args)
	{
		NavigationEvents::NavigateMapArgs* mapArgs = static_cast<NavigationEvents::NavigateMapArgs*>(args->getUserData());

		if (mapArgs != nullptr)
		{
			PlatformerMap::instance->loadMap(mapArgs->levelMap);
			GlobalDirector::loadScene(PlatformerMap::instance);
		}
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(PlatformerMap::onKeyPressed, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(PlatformerMap::onMouseWheelScroll, this);

	this->optionsMenu->setBackClickCallback(CC_CALLBACK_0(PlatformerMap::onOptionsExit, this));
	this->pauseMenu->setResumeCallback(CC_CALLBACK_0(PlatformerMap::onResumeClick, this));
	this->pauseMenu->setOptionsCallback(CC_CALLBACK_0(PlatformerMap::onOptionsClick, this));
	this->pauseMenu->setExitCallback(CC_CALLBACK_0(PlatformerMap::onExitClick, this));

	this->addEventListener(mouseListener);
	this->addEventListener(keyboardListener);
}

void PlatformerMap::loadMap(SerializableMap* serializableMap)
{
	this->map = serializableMap;
	this->mapNode->removeAllChildren();

	this->developerHud->loadMap(serializableMap);

	if (this->map != nullptr)
	{
		GameUtils::changeParent(this->map, this->mapNode, false);
		GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	}
}

void PlatformerMap::resume(void)
{
	if (PlatformerMap::hackerMode)
	{
		this->toggleHackerMode();
	}

	IMap::resume();
}

void PlatformerMap::update(float dt)
{
	IMap::update(dt);
}

void PlatformerMap::onMouseWheelScroll(EventMouse* event)
{
	if (this->developerMode)
	{
		float delta = event->getScrollY() * 64.0f;
		GameCamera::getInstance()->setCameraDistance(GameCamera::getInstance()->getCameraDistance() + delta);
	}
}

void PlatformerMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			this->openPauseMenu();
			event->stopPropagation();
			break;
		}
		case EventKeyboard::KeyCode::KEY_GRAVE:
		{
			this->toggleDeveloperMode();
			event->stopPropagation();
			break;
		}
		case EventKeyboard::KeyCode::KEY_TAB:
		{
			this->toggleHackerMode();
			event->stopPropagation();
			break;
		}
		default:
		{
			break;
		}
	}
}

void PlatformerMap::toggleDeveloperMode()
{
	this->developerMode = !this->developerMode;

	if (this->developerMode)
	{
		this->developerHud->setVisible(true);
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		Director::getInstance()->setDisplayStats(true);
	}
	else
	{
		this->developerHud->setVisible(false);
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
		Director::getInstance()->setDisplayStats(false);
	}
}

void PlatformerMap::toggleHackerMode()
{
	PlatformerMap::hackerMode = !PlatformerMap::hackerMode;

	if (PlatformerMap::hackerMode)
	{
		this->map->hackerModeEnable();
		this->mapNode->setVisible(true);
		this->hud->setVisible(false);
		this->mouseLayer->setVisible(false);

		this->hackerModeBackground->setVisible(true);
		this->hackerModeRain->setVisible(true);
		this->hackerModeHud->setVisible(true);

		GameUtils::focus(this->hackerModeHud);
	}
	else
	{
		this->map->hackerModeDisable();
		this->mapNode->setVisible(true);
		this->hud->setVisible(true);
		this->mouseLayer->setVisible(true);

		this->hackerModeBackground->setVisible(false);
		this->hackerModeRain->setVisible(false);
		this->hackerModeHud->setVisible(false);

		GameUtils::resumeAll();
	}
}

void PlatformerMap::onOptionsExit()
{
	this->optionsMenu->setVisible(false);
	this->openPauseMenu();
}

void PlatformerMap::openPauseMenu()
{
	this->menuBackDrop->setOpacity(196);
	this->pauseMenu->setVisible(true);
	GameUtils::focus(this->pauseMenu);
}

void PlatformerMap::onResumeClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	GameUtils::focus(this);
}

void PlatformerMap::onOptionsClick()
{
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(true);
	GameUtils::focus(this->optionsMenu);
}

void PlatformerMap::onExitClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	NavigationEvents::navigateTitle();
}
