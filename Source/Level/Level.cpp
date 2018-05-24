#include "Level.h"

bool Level::hackerMode = false;

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
	this->hackerModeHud = HackerModeHud::create();
	this->gamePostProcessInversion = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_Inverse);
	this->gamePostProcessNightVision = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_NightVision);
	this->camera = LevelCamera::create();
	this->mapNode = Node::create();

	this->camera->setScrollOffset(Vec2(64.0f, 32.0f));
	this->camera->setFollowSpeed(Vec2(0.075f, 0.075f));

	this->addChild(InputManager::claimInstance());
	this->addChild(this->hackerModeBackground);
	this->addChild(this->hackerModeRain);
	this->addChild(this->hackerModePostProcessGlow);
	this->addChild(this->mapNode);
	this->addChild(this->gamePostProcessInversion);
	this->addChild(this->gamePostProcessNightVision);
	this->addChild(this->hud);
	this->addChild(this->hackerModeHud);
	this->addChild(Mouse::create());
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
