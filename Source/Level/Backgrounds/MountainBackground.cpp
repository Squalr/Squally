#include "MountainBackground.h"

MountainBackground* MountainBackground::create()
{
	MountainBackground* newBackground = new MountainBackground();

	newBackground->autorelease();

	return newBackground;
}

MountainBackground::MountainBackground()
{
	this->background = Sprite::create(Resources::Ingame_Background_Day_Sky);
	this->clouds = InfiniteParallaxNode::create(Resources::Ingame_Background_Day_Clouds_01);
	this->mountains = ParallaxNode::create();
	this->mountains2 = ParallaxNode::create();
	this->trees1 = ParallaxNode::create();
	this->trees2 = ParallaxNode::create();
	this->trees3 = ParallaxNode::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background->setPosition(Vec2(this->background->getContentSize().width / 2, this->background->getContentSize().height / 2));

	this->clouds->setPosition(Vec2(0, 720.0f));
	this->clouds->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-16.0f, 0))));

	Sprite* mountainSprite = Sprite::create(Resources::Ingame_Background_Day_Mountains_01);
	this->mountains->addChild(mountainSprite, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->mountains->setPosition(Vec2(mountainSprite->getContentSize().width / 2, 320.0f));

	Sprite* mountainSprite2 = Sprite::create(Resources::Ingame_Background_Day_Mountains_02);
	this->mountains2->addChild(mountainSprite2, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->mountains2->setPosition(Vec2(mountainSprite2->getContentSize().width / 2, 224.0f));

	Sprite* treesSprite1 = Sprite::create(Resources::Ingame_Background_Day_Trees_01);
	this->trees1->addChild(treesSprite1, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->trees1->setPosition(Vec2(treesSprite1->getContentSize().width / 2, 192.0f));

	Sprite* treesSprite2 = Sprite::create(Resources::Ingame_Background_Day_Trees_02);
	this->trees2->addChild(treesSprite2, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->trees2->setPosition(Vec2(treesSprite2->getContentSize().width / 2, 128.0f));

	Sprite* treesSprite3 = Sprite::create(Resources::Ingame_Background_Day_Trees_03);
	this->trees3->addChild(treesSprite3, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->trees3->setPosition(Vec2(treesSprite3->getContentSize().width / 2, 96.0f));

	this->addChild(this->background);
	this->addChild(this->clouds);
	this->addChild(this->mountains);
	this->addChild(this->mountains2);
	this->addChild(this->trees1);
	this->addChild(this->trees2);
	this->addChild(this->trees3);

	this->scheduleUpdate();
}

MountainBackground::~MountainBackground()
{
}

void MountainBackground::update(float dt)
{
	Layer::update(dt);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float widthOffset = Director::getInstance()->getVisibleSize().width / 2;

	this->mountains->runAction(MoveTo::create(0.0f, Vec2(-LevelCamera::cameraOffset.x / 100.0f, this->mountains->getPosition().y)));
	this->mountains2->runAction(MoveTo::create(0.0f, Vec2(-LevelCamera::cameraOffset.x / 80.0f, this->mountains2->getPosition().y)));
	this->trees1->runAction(MoveTo::create(0.0f, Vec2(-LevelCamera::cameraOffset.x / 60.0f, this->trees1->getPosition().y)));
	this->trees2->runAction(MoveTo::create(0.0f, Vec2(-LevelCamera::cameraOffset.x / 40.0f, this->trees2->getPosition().y)));
	this->trees3->runAction(MoveTo::create(0.0f, Vec2(-LevelCamera::cameraOffset.x / 20.0f, this->trees3->getPosition().y)));
}
