#include "Level.h"
#include "Resources.h"
#include "TileCollision.h"
#include "../Collision/CollisionGroups.h"
#include "../Entities/Player.h"
#include "../GUI/Menus/PauseMenu.h"

Level::Level()
{
	if (!Scene::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	// Physics / collision debugging
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -768.0f));

	this->backGroundLayer = Layer::create();
	this->tileLayer = Layer::create();
	this->entityLayer = Layer::create();
	this->playerLayer = Layer::create();
	this->enemyLayer = Layer::create();

	this->pauseMenu = new PauseMenu();

	this->LoadLevel();

	this->backGroundLayer->addChild(this->backGround);
	this->entityLayer->addChild(this->playerLayer);
	this->entityLayer->addChild(this->enemyLayer);

	this->addChild(this->backGroundLayer);
	this->addChild(this->tileLayer);
	this->addChild(this->entityLayer);

	this->scheduleUpdate();
}

Level::~Level()
{
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
	Scene::update(dt);

	float widthOffset = Director::getInstance()->getVisibleSize().width / 2;
	float playerXOffset = this->player->getPositionX() - this->player->GetWidth();

	this->playerLayer->setPositionX(widthOffset - playerXOffset);
	this->tileLayer->setPositionX(widthOffset - playerXOffset);

	float heightOffset = Director::getInstance()->getVisibleSize().height / 2;
	float playerYOffset = this->player->getPositionY() - this->player->GetHeight();

	this->playerLayer->setPositionY(heightOffset - playerYOffset);
	this->tileLayer->setPositionY(heightOffset - playerYOffset);
}

void Level::LoadLevel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->backGround = Sprite::create(Resources::Background_GrassBG);
	this->backGround->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->backGround->getContentSize().height / 2));


	TMXTiledMap* map = TMXTiledMap::create(Resources::Levels_Debug);
	TMXLayer* midGround = map->getLayer("midground");
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
	TileCollision::InitializeCollision(map, midGround);

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
