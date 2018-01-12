#include "Level.h"

Size Level::mapSize = Size::ZERO;

Level* Level::create(std::string levelResourceFilePath)
{
	Level* level = new Level(levelResourceFilePath);

	level->autorelease();

	return level;
}

Level::Level(std::string levelResourceFilePath)
{
	if (!FadeScene::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	// Physics / collision debugging
	// this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

	experimental::TMXTiledMap* map = experimental::TMXTiledMap::create(levelResourceFilePath);
	Level::mapSize = Size(map->getMapSize().width * map->getTileSize().width, map->getMapSize().height * map->getTileSize().height);

	this->background = LevelParser::initializeBackground(map);
	this->backgroundPostProcess = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_GrayBlur);
	this->backgroundParallax = LevelParser::initializeParallaxObjects(map, "background-parallax");
	this->backgroundLayer = LevelParser::initializeTileLayer(map, "background");
	this->backgroundDecor = LevelParser::initializeDecor(map, "background-decor");
	this->midgroundLayer = LevelParser::initializeTileLayer(map, "midground");
	this->midgroundDecor = LevelParser::initializeDecor(map, "midground-decor");
	this->foregroundLayer = LevelParser::initializeTileLayer(map, "foreground");
	this->foregroundDecor = LevelParser::initializeDecor(map, "foreground-decor");
	this->objectLayer = LevelParser::initializeObjects(map);
	this->entityLayer = LevelParser::initializeEntities(map);
	this->collisionLayer = LevelParser::initializeCollision(map);
	this->environmentLayer = LevelParser::initializeEnvironment(map);
	this->gameLayers = Layer::create();
	this->gamePostProcess = PostProcess::create(Resources::Shaders_Vertex_Generic, Resources::Shaders_Fragment_GrayBlur);
	this->hud = HUD::create();
	this->addChild(InputManager::claimInstance());

	this->addChild(this->background);
	this->addChild(this->backgroundPostProcess);
	this->gameLayers->addChild(this->backgroundParallax);
	this->gameLayers->addChild(this->backgroundLayer);
	this->gameLayers->addChild(this->backgroundDecor);
	this->gameLayers->addChild(this->midgroundLayer);
	this->gameLayers->addChild(this->midgroundDecor);
	this->gameLayers->addChild(this->objectLayer);
	this->gameLayers->addChild(this->entityLayer);
	this->gameLayers->addChild(this->foregroundLayer);
	this->gameLayers->addChild(this->foregroundDecor);
	this->gameLayers->addChild(this->collisionLayer);
	this->gameLayers->addChild(this->environmentLayer);
	this->addChild(this->gameLayers);
	this->addChild(this->gamePostProcess);
	this->addChild(this->hud);

	this->scheduleUpdate();
	this->update(0.0f);

	this->initializeListeners();
}

Level::~Level()
{
}

void Level::onEnter()
{
	FadeScene::onEnter();

	this->addChild(Mouse::claimInstance());
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
	LevelCamera::cameraPosition.x = min(LevelCamera::cameraPosition.x, this->mapSize.width - visibleSize.width);
	LevelCamera::cameraPosition.x = max(LevelCamera::cameraPosition.x, 0.0f);

	LevelCamera::cameraPosition.y = min(LevelCamera::cameraPosition.y, this->mapSize.height - visibleSize.height);
	LevelCamera::cameraPosition.y = max(LevelCamera::cameraPosition.y, 0.0f);

	// Scroll world
	this->gameLayers->setPosition(-LevelCamera::cameraPosition);
}

void Level::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Level::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void Level::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->pushScene(PauseMenu::create());
		break;
	}
}

void Level::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	this->background->setVisible(true);
	this->backgroundPostProcess->draw(this->background);
	this->background->setVisible(false);

	this->gameLayers->setVisible(true);
	this->gamePostProcess->draw(this->gameLayers);
	this->gameLayers->setVisible(false);
}
