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
	this->hud = HUD::create();

	this->addChild(InputManager::claimInstance());
	this->addChild(this->background);
	this->addChild(this->backgroundParallax);
	this->addChild(this->backgroundLayer);
	this->addChild(this->backgroundDecor);
	this->addChild(this->midgroundLayer);
	this->addChild(this->midgroundDecor);
	this->addChild(this->objectLayer);
	this->addChild(this->entityLayer);
	this->addChild(this->foregroundLayer);
	this->addChild(this->foregroundDecor);
	this->addChild(this->collisionLayer);
	this->addChild(this->environmentLayer);
	this->addChild(this->hud);
	this->addChild(Mouse::claimInstance());

	this->scheduleUpdate();
	this->update(0.0f);

	this->initializeListeners();
}

Level::~Level()
{
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
	this->backgroundParallax->setPosition(-LevelCamera::cameraPosition);
	this->backgroundLayer->setPosition(-LevelCamera::cameraPosition);
	this->backgroundDecor->setPosition(-LevelCamera::cameraPosition);
	this->midgroundLayer->setPosition(-LevelCamera::cameraPosition);
	this->midgroundDecor->setPosition(-LevelCamera::cameraPosition);
	this->objectLayer->setPosition(-LevelCamera::cameraPosition);
	this->entityLayer->setPosition(-LevelCamera::cameraPosition);
	this->collisionLayer->setPosition(-LevelCamera::cameraPosition);
	this->foregroundLayer->setPosition(-LevelCamera::cameraPosition);
	this->foregroundDecor->setPosition(-LevelCamera::cameraPosition);
	this->environmentLayer->setPosition(-LevelCamera::cameraPosition);
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
