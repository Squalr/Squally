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

	this->backGroundLayer->addChild(this->backGround);
	this->backGroundLayer->addChild(this->clouds);
	this->backGroundLayer->addChild(this->mountains);
	this->backGroundLayer->addChild(this->mountains2);
	this->backGroundLayer->addChild(this->trees1);
	this->backGroundLayer->addChild(this->trees2);
	this->backGroundLayer->addChild(this->trees3);
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
	delete(this->player);
}

void Level::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();
}

void Level::update(float dt)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Scene::update(dt);

	float widthOffset = Director::getInstance()->getVisibleSize().width / 2;
	float playerXOffset = this->player->getPositionX() - this->player->GetWidth();

	this->mountains->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 100.0f, this->mountains->getPosition().y)));
	this->mountains2->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 80.0f, this->mountains2->getPosition().y)));
	this->trees1->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 60.0f, this->trees1->getPosition().y)));
	this->trees2->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 40.0f, this->trees2->getPosition().y)));
	this->trees3->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 20.0f, this->trees3->getPosition().y)));

	this->playerLayer->setPositionX(widthOffset - playerXOffset);
	this->tileLayer->setPositionX(widthOffset - playerXOffset);

	float heightOffset = Director::getInstance()->getVisibleSize().height / 2;
	float playerYOffset = this->player->getPositionY() - this->player->GetHeight();

	this->playerLayer->setPositionY(heightOffset - playerYOffset);
	this->tileLayer->setPositionY(heightOffset - playerYOffset);

	this->clouds->updatePosition();
}

void Level::LoadLevel(std::string levelResourceFilePath)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->backGround = Sprite::create(Resources::Ingame_Background_Day_Sky);
	this->backGround->setPosition(Vec2(this->backGround->getContentSize().width / 2, this->backGround->getContentSize().height / 2));

	this->clouds = InfiniteParallaxNode::create();
	Sprite* cloudSprite = Sprite::create(Resources::Ingame_Background_Day_Clouds_01);
	this->clouds->addChild(Sprite::create(Resources::Ingame_Background_Day_Clouds_01), 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->clouds->addChild(Sprite::create(Resources::Ingame_Background_Day_Clouds_01), 0, Vec2(1.0f, 1.0f), Vec2(cloudSprite->getContentSize().width - 2, 0.0f));
	this->clouds->setPosition(Vec2(cloudSprite->getContentSize().width / 2, 720.0f));
	this->clouds->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-16.0f, 0))));

	Sprite* mountainSprite = Sprite::create(Resources::Ingame_Background_Day_Mountains_01);
	this->mountains = ParallaxNode::create();
	this->mountains->addChild(mountainSprite, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->mountains->setPosition(Vec2(mountainSprite->getContentSize().width / 2, 320.0f));

	Sprite* mountainSprite2 = Sprite::create(Resources::Ingame_Background_Day_Mountains_02);
	this->mountains2 = ParallaxNode::create();
	this->mountains2->addChild(mountainSprite2, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->mountains2->setPosition(Vec2(mountainSprite2->getContentSize().width / 2, 224.0f));

	Sprite* treesSprite1 = Sprite::create(Resources::Ingame_Background_Day_Trees_01);
	this->trees1 = ParallaxNode::create();
	this->trees1->addChild(treesSprite1, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->trees1->setPosition(Vec2(treesSprite1->getContentSize().width / 2, 192.0f));

	Sprite* treesSprite2 = Sprite::create(Resources::Ingame_Background_Day_Trees_02);
	this->trees2 = ParallaxNode::create();
	this->trees2->addChild(treesSprite2, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->trees2->setPosition(Vec2(treesSprite2->getContentSize().width / 2, 128.0f));

	Sprite* treesSprite3 = Sprite::create(Resources::Ingame_Background_Day_Trees_03);
	this->trees3 = ParallaxNode::create();
	this->trees3->addChild(treesSprite3, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->trees3->setPosition(Vec2(treesSprite3->getContentSize().width / 2, 96.0f));

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
