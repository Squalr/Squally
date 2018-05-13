#include "Level.h"

bool Level::hackerMode = false;

Level* Level::create()
{
	Level* level = new Level();

	level->autorelease();

	return level;
}

Level::Level()
{
	if (!FadeScene::initWithPhysics())
	{
		throw std::uncaught_exception();
	}
}

Level::~Level()
{
}

void Level::onEnter()
{
	FadeScene::onEnter();

	this->addChild(Mouse::claimInstance());

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();
}

void Level::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->hackerModeBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void Level::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Level::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Level::loadLevel(LevelMap* levelMap)
{
	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -512.0f));

	this->hackerModeBackground = Sprite::create(Resources::Backgrounds_MatrixRain_HackerModeBackground);
	this->hackerModeRain = MatrixRain::create();
	this->hackerModePostProcessGlow = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_GrayBlur);
	this->hud = Hud::create();
	this->hackerModeHud = HackerModeHud::create();
	this->gamePostProcessInversion = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_Inverse);
	this->gamePostProcessNightVision = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_NightVision);

	this->map = levelMap;

	this->addChild(InputManager::claimInstance());

	this->addChild(this->hackerModeBackground);
	this->addChild(this->hackerModeRain);
	this->addChild(this->hackerModePostProcessGlow);
	this->addChild(this->map);
	this->addChild(this->gamePostProcessInversion);
	this->addChild(this->gamePostProcessNightVision);
	this->addChild(this->hud);
	this->addChild(this->hackerModeHud);
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

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Handle camera scrolling from player traveling past scroll distance
	if (LevelCamera::cameraPosition.x < Player::position.x - LevelCamera::cameraScrollOffsetX - visibleSize.width / 2)
	{
		LevelCamera::cameraPosition.x = Player::position.x - LevelCamera::cameraScrollOffsetX - visibleSize.width / 2;
	}
	else if (LevelCamera::cameraPosition.x > Player::position.x + LevelCamera::cameraScrollOffsetX - visibleSize.width / 2)
	{
		LevelCamera::cameraPosition.x = Player::position.x + LevelCamera::cameraScrollOffsetX - visibleSize.width / 2;
	}

	if (LevelCamera::cameraPosition.y < Player::position.y - LevelCamera::cameraScrollOffsetY - visibleSize.height / 2)
	{
		LevelCamera::cameraPosition.y = Player::position.y - LevelCamera::cameraScrollOffsetY - visibleSize.height / 2;
	}
	else if (LevelCamera::cameraPosition.y > Player::position.y + LevelCamera::cameraScrollOffsetY - visibleSize.height / 2)
	{
		LevelCamera::cameraPosition.y = Player::position.y + LevelCamera::cameraScrollOffsetY - visibleSize.height / 2;
	}

	// Prevent camera from leaving level bounds
	LevelCamera::cameraPosition.x = min(LevelCamera::cameraPosition.x, LevelMap::mapSize.width - visibleSize.width);
	LevelCamera::cameraPosition.x = max(LevelCamera::cameraPosition.x, 0.0f);

	LevelCamera::cameraPosition.y = min(LevelCamera::cameraPosition.y, LevelMap::mapSize.height - visibleSize.height);
	LevelCamera::cameraPosition.y = max(LevelCamera::cameraPosition.y, 0.0f);

	// Scroll world // TODO: Trigger scroll event or something
	this->map->setPosition(-LevelCamera::cameraPosition);
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
		NavigationEvents::navigate(NavigationEvents::GameScreen::Pause);
		event->stopPropagation();
		break;
	case EventKeyboard::KeyCode::KEY_GRAVE:
		if (this->getPhysicsWorld()->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL)
		{
			this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
			Director::getInstance()->setDisplayStats(false);
		}
		else
		{
			this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
			Director::getInstance()->setDisplayStats(true);
		}
		event->stopPropagation();
		break;
	case EventKeyboard::KeyCode::KEY_TAB:
		this->enableHackerMode();
		event->stopPropagation();
		break;
	}
}

void Level::enableHackerMode()
{
	Level::hackerMode = true;
	GameUtils::focus(this->hackerModeHud);
}

void Level::disableHackerMode()
{
	Level::hackerMode = false;
	GameUtils::resumeAll();
}

void Level::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	// Manual drawing (to apply post processing effects)
	if (Level::hackerMode)
	{
		// Set visibility of desired layers
		this->hackerModeBackground->setVisible(true);
		this->hackerModeRain->setVisible(true);
		this->hackerModePostProcessGlow->setVisible(true);
		this->hud->setVisible(false);
		this->hackerModeHud->setVisible(true);
		this->gamePostProcessInversion->setVisible(true);
		this->gamePostProcessNightVision->setVisible(true);

		this->map->hackerModeEnable();

		// Draw hackermode level
		this->hackerModeRain->draw();

		this->gamePostProcessInversion->draw(this->map);
		this->gamePostProcessNightVision->draw(this->gamePostProcessInversion);

		// Prevent double render
		this->map->setVisible(false);
	}
	else
	{
		// Set visibility of desired layers
		this->hackerModeBackground->setVisible(false);
		this->hackerModeRain->setVisible(false);
		this->hackerModePostProcessGlow->setVisible(false);
		this->hud->setVisible(true);
		this->hackerModeHud->setVisible(false);
		this->gamePostProcessInversion->setVisible(false);
		this->gamePostProcessNightVision->setVisible(false);

		this->map->hackerModeDisable();
	}
}
