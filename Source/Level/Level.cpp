#include "Level.h"

bool Level::hackerMode = false;
bool Level::developerMode = false;

Level* Level::create()
{
	Level* instance = new Level();

	instance->autorelease();

	return instance;
}

Level::Level()
{
	if (!FadeScene::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -768.0f));

	this->hackerModeBackground = Sprite::create(Resources::Backgrounds_MatrixRain_HackerModeBackground);
	this->hackerModeRain = MatrixRain::create();
	this->hackerModePostProcessGlow = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_GrayBlur);
	this->hud = Hud::create();
	this->developerHud = DeveloperHud::create();
	this->hackerModeHud = HackerModeHud::create();
	this->gamePostProcessInversion = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_Inverse);
	this->gamePostProcessNightVision = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_NightVision);
	this->camera = LevelCamera::create();
	this->mapNode = Node::create();
	this->mouse = Mouse::create();
	this->uiLayer = UILayer::create();

	this->camera->setScrollOffset(Vec2(64.0f, 32.0f));
	this->camera->setFollowSpeed(Vec2(0.075f, 0.075f));

	// Call disable to initialize hidden hackermode stuff
	this->disableHackerMode();
	this->developerHud->setVisible(false);

	this->addChild(InputManager::claimInstance());
	this->addChild(this->hackerModeBackground);
	this->addChild(this->hackerModeRain);
	this->addChild(this->hackerModePostProcessGlow);
	this->addChild(this->mapNode);
	this->addChild(this->gamePostProcessInversion);
	this->addChild(this->gamePostProcessNightVision);
	this->addChild(this->uiLayer);
	this->uiLayer->addChild(this->hud);
	this->uiLayer->addChild(this->developerHud);
	this->uiLayer->addChild(this->hackerModeHud);
	this->uiLayer->addChild(this->mouse);
	this->addChild(this->camera);
}

Level::~Level()
{
}

void Level::onEnter()
{
	FadeScene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();
}

void Level::initializePositions()
{
}

void Level::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	listener->onKeyPressed = CC_CALLBACK_2(Level::onKeyPressed, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(Level::onMouseWheelScroll, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Level::loadLevel(LevelMap* levelMap)
{
	this->map = levelMap;

	this->mapNode->removeAllChildren();
	this->mapNode->addChild(this->map);

	this->camera->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	this->camera->setTarget(Player::getInstance());
}

void Level::resume(void)
{
	if (Level::hackerMode)
	{
		this->disableHackerMode();
	}

	Node::resume();
}

void Level::update(float dt)
{
	FadeScene::update(dt);
}

void Level::onMouseWheelScroll(EventMouse* event)
{
	if (this->developerMode)
	{
		float delta = event->getScrollY() * 64.0f;

		Camera::getDefaultCamera()->setPositionZ(Camera::getDefaultCamera()->getPositionZ() + delta);
	}
}

void Level::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isRunning() || !this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		PauseEvents::pauseLevel(PauseEvents::PauseEventArgs(this->map->getMapFileName(), Player::getInstance()->getPosition()));
		event->stopPropagation();
		break;
	case EventKeyboard::KeyCode::KEY_GRAVE:
		this->toggleDeveloperMode();
		event->stopPropagation();
		break;
	case EventKeyboard::KeyCode::KEY_TAB:
		this->enableHackerMode();
		event->stopPropagation();
		break;
	}
}

void Level::toggleDeveloperMode()
{
	this->developerMode = !this->developerMode;

	if (this->developerMode)
	{
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		Director::getInstance()->setDisplayStats(true);
	}
	else
	{
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
		Director::getInstance()->setDisplayStats(false);
	}
}

void Level::enableHackerMode()
{
	Level::hackerMode = true;

	this->map->hackerModeEnable();
	this->mapNode->setVisible(true);
	this->map->setVisible(true);
	this->hud->setVisible(false);
	this->mouse->setVisible(false);

	this->hackerModeBackground->setVisible(true);
	this->hackerModeRain->setVisible(true);
	this->hackerModePostProcessGlow->setVisible(true);
	this->hackerModeHud->setVisible(true);
	this->gamePostProcessInversion->setVisible(true);
	this->gamePostProcessNightVision->setVisible(true);

	GameUtils::focus(this->hackerModeHud);
}

void Level::disableHackerMode()
{
	Level::hackerMode = false;

	this->map->hackerModeDisable();
	this->mapNode->setVisible(true);
	this->map->setVisible(true);
	this->hud->setVisible(true);
	this->mouse->setVisible(true);

	this->hackerModeBackground->setVisible(false);
	this->hackerModeRain->setVisible(false);
	this->hackerModePostProcessGlow->setVisible(false);
	this->hackerModeHud->setVisible(false);
	this->gamePostProcessInversion->setVisible(false);
	this->gamePostProcessNightVision->setVisible(false);

	GameUtils::resumeAll();
}

void Level::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (Level::hackerMode)
	{
		// Zac : well, using the camera correctly fucked my shaders -- these apparently render at the origin rather than the camera position
		/*
		this->mapNode->setVisible(true);

		// Draw map with shaders
		this->gamePostProcessInversion->draw(this->map);
		this->gamePostProcessNightVision->draw(this->gamePostProcessInversion);

		// Prevent double render
		this->mapNode->setVisible(false);
		*/
	}
}
