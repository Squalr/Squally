#include "PlatformerMap.h"

bool PlatformerMap::hackerMode = false;
bool PlatformerMap::developerMode = false;

PlatformerMap* PlatformerMap::create()
{
	PlatformerMap* instance = new PlatformerMap();

	instance->autorelease();

	return instance;
}

PlatformerMap::PlatformerMap()
{
	if (!IMap::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -768.0f));

	this->hackerModeBackground = Sprite::create(BackgroundResources::Platformer_MatrixRain_HackerModeBackground);
	this->hackerModeRain = MatrixRain::create();
	this->hackerModePostProcessGlow = PostProcess::create(ShaderResources::Vertex_Generic, ShaderResources::Fragment_GrayBlur);
	this->hud = Hud::create();
	this->developerHud = DeveloperHud::create();
	this->hackerModeHud = HackerModeHud::create(CC_CALLBACK_0(PlatformerMap::toggleHackerMode, this));
	this->gamePostProcessInversion = PostProcess::create(ShaderResources::Vertex_Generic, ShaderResources::Fragment_Inverse);
	this->gamePostProcessNightVision = PostProcess::create(ShaderResources::Vertex_Generic, ShaderResources::Fragment_NightVision);
	this->camera = GameCamera::create();
	this->mapNode = Node::create();
	this->mouseLayer = Node::create();

	this->camera->setScrollOffset(Vec2(64.0f, 32.0f));
	this->camera->setFollowSpeed(Vec2(0.075f, 0.075f));

	this->hackerModeBackground->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->hackerModeBackground->setVisible(false);
	this->hackerModeRain->setVisible(false);
	this->hackerModePostProcessGlow->setVisible(false);
	this->hackerModeHud->setVisible(false);
	this->gamePostProcessInversion->setVisible(false);
	this->gamePostProcessNightVision->setVisible(false);
	this->developerHud->setVisible(false);

	this->addChild(InputManager::claimInstance());
	this->addChild(this->hackerModeBackground);
	this->addChild(this->hackerModeRain);
	this->addChild(this->hackerModePostProcessGlow);
	this->addChild(this->mapNode);
	this->addChild(this->gamePostProcessInversion);
	this->addChild(this->gamePostProcessNightVision);
	this->addChild(this->hud);
	this->addChild(this->developerHud);
	this->addChild(this->hackerModeHud);
	this->mouseLayer->addChild(Mouse::create());
	this->addChild(this->mouseLayer);
	this->addChild(this->camera);
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	IMap::onEnter();

	this->scheduleUpdate();
}

void PlatformerMap::initializePositions()
{
	IMap::initializePositions();
}

void PlatformerMap::initializeListeners()
{
	IMap::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(PlatformerMap::onKeyPressed, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(PlatformerMap::onMouseWheelScroll, this);

	this->addEventListener(mouseListener);
	this->addEventListener(keyboardListener);
}

void PlatformerMap::loadMap(SerializableMap* serializableMap)
{
	this->map = serializableMap;
	this->mapNode->removeAllChildren();

	GameUtils::changeParent(this->map, this->mapNode, false);

	this->developerHud->loadMap(serializableMap);

	this->camera->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	this->camera->setTarget(Squally::getInstance());
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
		this->camera->setCameraDistance(this->camera->getCameraDistance() + delta);
	}
}

void PlatformerMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isRunning() || !this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			NavigationEvents::navigate(NavigationEvents::GameScreen::Pause);
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
		this->map->setVisible(true);
		this->hud->setVisible(false);
		this->mouseLayer->setVisible(false);

		this->hackerModeBackground->setVisible(true);
		this->hackerModeRain->setVisible(true);
		this->hackerModePostProcessGlow->setVisible(true);
		this->hackerModeHud->setVisible(true);
		this->gamePostProcessInversion->setVisible(true);
		this->gamePostProcessNightVision->setVisible(true);

		GameUtils::focus(this->hackerModeHud);
	}
	else
	{
		this->map->hackerModeDisable();
		this->mapNode->setVisible(true);
		this->map->setVisible(true);
		this->hud->setVisible(true);
		this->mouseLayer->setVisible(true);

		this->hackerModeBackground->setVisible(false);
		this->hackerModeRain->setVisible(false);
		this->hackerModePostProcessGlow->setVisible(false);
		this->hackerModeHud->setVisible(false);
		this->gamePostProcessInversion->setVisible(false);
		this->gamePostProcessNightVision->setVisible(false);

		GameUtils::resumeAll();
	}
}

void PlatformerMap::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (PlatformerMap::hackerMode)
	{
		// Zac : well, using the camera correctly fucked my shaders -- these apparently render at the origin rather than the camera position
		/*this->mapNode->setVisible(true);

		// Draw map with shaders
		this->gamePostProcessInversion->draw(this->mapNode);
		this->gamePostProcessNightVision->draw(this->gamePostProcessInversion);

		// Prevent double render
		this->mapNode->setVisible(false);*/
	}
}
