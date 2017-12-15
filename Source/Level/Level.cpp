#include "Level.h"

Level::Level(std::string levelResourceFilePath)
{
	if (!Scene::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	// Physics / collision debugging
	// this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -768.0f));

	this->backGroundLayer = Layer::create();
	this->tileLayer = Layer::create();
	this->entityLayer = Layer::create();
	this->playerLayer = Layer::create();
	this->enemyLayer = Layer::create();
	this->environmentLayer = Layer::create();

	this->pauseMenu = new PauseMenu();

	this->LoadLevel(levelResourceFilePath);

	this->backGroundLayer->addChild(this->midGround);
	this->backGroundLayer->addChild(this->backGround);
	this->entityLayer->addChild(this->playerLayer);
	this->entityLayer->addChild(this->enemyLayer);

	this->addChild(this->backGroundLayer);
	this->addChild(this->tileLayer);
	this->addChild(this->entityLayer);
	this->addChild(this->environmentLayer);

	this->scheduleUpdate();
}

Level::~Level()
{
	delete(this->midGround);
	delete(this->backGround);
	delete(this->player);
}

void Level::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();
}

void Level::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Scene::update(dt);

	float widthOffset = Director::getInstance()->getVisibleSize().width / 2;
	float playerXOffset = this->player->getPositionX() - this->player->GetWidth();

	this->backGround->runAction(MoveTo::create(0.0f, Vec2(playerXOffset / 10.0f, visibleSize.height)));

	this->playerLayer->setPositionX(widthOffset - playerXOffset);
	this->tileLayer->setPositionX(widthOffset - playerXOffset);

	float heightOffset = Director::getInstance()->getVisibleSize().height / 2;
	float playerYOffset = this->player->getPositionY() - this->player->GetHeight();

	this->playerLayer->setPositionY(heightOffset - playerYOffset);
	this->tileLayer->setPositionY(heightOffset - playerYOffset);

	// this->backGround->updatePosition();
	this->midGround->updatePosition();
}

void Level::LoadLevel(std::string levelResourceFilePath)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->backGround = InfiniteParallaxNode::create();
	// this->backGround->addChild(Sprite::create(Resources::Ingame_Background_Day_Sky), 0, Vec2(0.5f, 0.5f), Vec2::ZERO);
	this->backGround->addChild(Sprite::create(Resources::Ingame_Background_Day_Mountains_01), 0, Vec2(0.25f, 0.25f), Vec2::ZERO);
	this->backGround->setPosition(Vec2(0, origin.y + visibleSize.height - this->backGround->getContentSize().height / 2));

	this->midGround = InfiniteParallaxNode::create();
	Sprite* clouds = Sprite::create(Resources::Ingame_Background_Day_Clouds_01);
	this->midGround->addChild(Sprite::create(Resources::Ingame_Background_Day_Clouds_01), 0, Vec2(0.75f, 0.75f), Vec2::ZERO);
	this->midGround->addChild(clouds, 0, Vec2(0.75f, 0.75f), Vec2(clouds->getContentSize().width, 0.0f));
	this->midGround->setPosition(Vec2(0, origin.y + visibleSize.height + 256.0f));
	this->midGround->runAction(RepeatForever::create(MoveBy::create(0.25f, Vec2(-100.0f, 0))));

	this->environmentLayer->addChild(ParticleRain::create());

	TMXTiledMap* map = TMXTiledMap::create(levelResourceFilePath);
	TMXLayer* background = map->getLayer("background");
	TMXLayer* midGround = map->getLayer("midground");
	TMXLayer* foreground = map->getLayer("foreground");
	ValueVector objects = map->getObjectGroup("objects")->getObjects();

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
			this->player = new Player();
			this->player->setPosition(Vec2(object.at("x").asFloat(), object.at("y").asFloat()));
			this->playerLayer->addChild(this->player);
		}
	}

	// Create midground
	TileCollision::InitializeCollision(map, midGround, TileCollision::All);
	TileCollision::InitializeCollision(map, foreground, TileCollision::Liquid);

	this->tileLayer->addChild(map);
}

void Level::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Level::OnKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void Level::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->pushScene(this->pauseMenu);
		break;
	}
}
