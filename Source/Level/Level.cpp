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
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

	this->backGroundLayer = Background::create();
	this->tileLayer = Layer::create();
	this->foregroundLayer = Layer::create();
	this->entityLayer = Layer::create();
	this->playerLayer = Layer::create();
	this->enemyLayer = Layer::create();
	this->environmentLayer = Layer::create();
	this->hud = HUD::create();

	this->loadLevel(levelResourceFilePath);

	this->entityLayer->addChild(this->playerLayer);
	this->entityLayer->addChild(this->enemyLayer);

	this->addChild(InputManager::claimInstance());
	this->addChild(this->backGroundLayer);
	this->addChild(this->tileLayer);
	this->addChild(this->entityLayer);
	this->addChild(this->foregroundLayer);
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

	float playerOffsetX = Director::getInstance()->getVisibleSize().width / 2 - this->player->getPositionX();
	float playerOffsetY = Director::getInstance()->getVisibleSize().height / 2 - this->player->getPositionY();

	// Handle camera scrolling from player traveling past scroll distance
	if (this->playerLayer->getPositionX() < playerOffsetX - LevelCamera::cameraScrollOffsetX)
	{
		LevelCamera::cameraOffset.x = playerOffsetX - LevelCamera::cameraScrollOffsetX;
	}
	else if (this->playerLayer->getPositionX() > playerOffsetX + LevelCamera::cameraScrollOffsetX)
	{
		LevelCamera::cameraOffset.x = playerOffsetX + LevelCamera::cameraScrollOffsetX;
	}

	if (this->playerLayer->getPositionY() < playerOffsetY - LevelCamera::cameraScrollOffsetY)
	{
		LevelCamera::cameraOffset.y = playerOffsetY - LevelCamera::cameraScrollOffsetY;
	}
	else if (this->playerLayer->getPositionY() > playerOffsetY + LevelCamera::cameraScrollOffsetY)
	{
		LevelCamera::cameraOffset.y = playerOffsetY + LevelCamera::cameraScrollOffsetY;
	}

	this->playerLayer->setPosition(LevelCamera::cameraOffset);
	this->enemyLayer->setPosition(LevelCamera::cameraOffset);
	this->tileLayer->setPosition(LevelCamera::cameraOffset);
	this->foregroundLayer->setPosition(LevelCamera::cameraOffset);
}

void Level::loadLevel(std::string levelResourceFilePath)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->environmentLayer->addChild(ParticleRain::create());

	experimental::TMXTiledMap* map = experimental::TMXTiledMap::create(levelResourceFilePath);
	experimental::TMXLayer* background = map->getLayer("background");
	experimental::TMXLayer* midGround = map->getLayer("midground");
	experimental::TMXLayer* foreground = map->getLayer("foreground");
	ValueVector objects = map->getObjectGroup("objects")->getObjects();
	ValueVector collisionObjects = map->getObjectGroup("collision")->getObjects();

	// Create entities
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();
		string type = object.at("type").asString();

		if (type == "spawn")
		{
			this->player = Player::create();
			this->player->setPosition(Vec2(object.at("x").asFloat(), object.at("y").asFloat()));
			this->playerLayer->addChild(this->player);
		}
		else if (type == "shroom")
		{
			Shroom* shroom = Shroom::create();
			shroom->setPosition(Vec2(object.at("x").asFloat(), object.at("y").asFloat()));
			this->enemyLayer->addChild(shroom);
		}
	}

	// Create midground
	Layer* collisionLayer = Collision::initializeCollision(collisionObjects);

	Node* backgroundNode = map->getChildren().at(0);
	Node* midgroundNode = map->getChildren().at(1);
	Node* foregroundNode = map->getChildren().at(2);

	map->removeAllChildren();

	this->tileLayer->addChild(backgroundNode);
	this->tileLayer->addChild(midgroundNode);
	this->tileLayer->addChild(collisionLayer);
	this->foregroundLayer->addChild(foregroundNode);
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
