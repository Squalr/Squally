#include "Level.h"

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

	this->background = LevelParser::initializeBackground(map);
	this->backgroundLayer = LevelParser::initializeBackgroundTiles(map);
	this->midgroundLayer = LevelParser::initializeMidgroundTiles(map);
	this->foregroundLayer = LevelParser::initializeForegroundTiles(map);
	this->objectLayer = LevelParser::initializeObjects(map);
	this->collisionLayer = LevelParser::initializeCollision(map);
	this->environmentLayer = LevelParser::initializeEnvironment(map);
	this->hud = HUD::create();

	this->addChild(InputManager::claimInstance());
	this->addChild(this->background);
	this->addChild(this->backgroundLayer);
	this->addChild(this->midgroundLayer);
	this->addChild(this->objectLayer);
	this->addChild(this->foregroundLayer);
	this->addChild(this->collisionLayer);
	this->addChild(this->environmentLayer);
	this->addChild(this->hud);

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

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float playerOffsetX = Director::getInstance()->getVisibleSize().width / 2 - Player::position.x;
	float playerOffsetY = Director::getInstance()->getVisibleSize().height / 2 - Player::position.y;

	// Handle camera scrolling from player traveling past scroll distance
	if (LevelCamera::cameraOffset.x < playerOffsetX - LevelCamera::cameraScrollOffsetX)
	{
		LevelCamera::cameraOffset.x = playerOffsetX - LevelCamera::cameraScrollOffsetX;
	}
	else if (LevelCamera::cameraOffset.x > playerOffsetX + LevelCamera::cameraScrollOffsetX)
	{
		LevelCamera::cameraOffset.x = playerOffsetX + LevelCamera::cameraScrollOffsetX;
	}

	if (LevelCamera::cameraOffset.y < playerOffsetY - LevelCamera::cameraScrollOffsetY)
	{
		LevelCamera::cameraOffset.y = playerOffsetY - LevelCamera::cameraScrollOffsetY;
	}
	else if (LevelCamera::cameraOffset.y > playerOffsetY + LevelCamera::cameraScrollOffsetY)
	{
		LevelCamera::cameraOffset.y = playerOffsetY + LevelCamera::cameraScrollOffsetY;
	}

	this->backgroundLayer->setPosition(LevelCamera::cameraOffset);
	this->midgroundLayer->setPosition(LevelCamera::cameraOffset);
	this->objectLayer->setPosition(LevelCamera::cameraOffset);
	this->collisionLayer->setPosition(LevelCamera::cameraOffset);
	this->foregroundLayer->setPosition(LevelCamera::cameraOffset);
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
