#include "Level.h"
#include "Resources.h"
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

	this->backGroundLayer = Layer::create();
	this->tileLayer = Layer::create();
	this->entityLayer = Layer::create();
	this->playerLayer = Layer::create();
	this->enemyLayer = Layer::create();

	this->pauseMenu = new PauseMenu();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* map = TMXTiledMap::create(Resources::Levels_Debug);
	TMXLayer* layer = map->getLayer("Midground");

	this->tileLayer->addChild(map);

	this->backGround = Sprite::create(Resources::Background_GrassBG);
	this->player = new Player();

	this->backGround->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->backGround->getContentSize().height / 2));
	this->player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->backGroundLayer->addChild(this->backGround);
	this->playerLayer->addChild(this->player);
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

	{
		float widthOffset = Director::getInstance()->getVisibleSize().width / 2;
		float playerOffset = this->player->getPositionX() - this->player->GetWidth();

		this->playerLayer->setPositionX(widthOffset - playerOffset);
		this->tileLayer->setPositionX(widthOffset - playerOffset);
	}
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
