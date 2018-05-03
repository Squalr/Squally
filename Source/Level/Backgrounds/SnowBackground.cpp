#include "SnowBackground.h"

SnowBackground* SnowBackground::create()
{
	SnowBackground* instance = new SnowBackground();

	instance->autorelease();

	return instance;
}

SnowBackground::SnowBackground()
{
	this->background = Sprite::create(Resources::Backgrounds_Snow_snowmountains_bg);
	this->layer6 = InfiniteParallaxNode::create(Resources::Backgrounds_Snow_snowmountains_fg);
	this->layer5 = InfiniteParallaxNode::create(Resources::Backgrounds_Snow_snowmountains_acc);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->layer6->setPosition(Vec2(this->layer6->getContentSize().width / 2, visibleSize.height / 2));
	this->layer5->setPosition(Vec2(this->layer5->getContentSize().width / 2, visibleSize.height / 2));

	this->layer6->setVisible(false);
	this->layer5->setVisible(false);

	this->addChild(this->background);
	this->addChild(this->layer6);
	this->addChild(this->layer5);

	this->scheduleUpdate();
}

SnowBackground::~SnowBackground()
{
}

void SnowBackground::update(float dt)
{
	Layer::update(dt);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float widthOffset = Director::getInstance()->getVisibleSize().width / 2;

	this->layer6->runAction(MoveTo::create(0.0f, Vec2(-LevelCamera::cameraPosition.x / 80.0f, this->layer6->getPosition().y)));
	this->layer5->runAction(MoveTo::create(0.0f, Vec2(-LevelCamera::cameraPosition.x / 60.0f, this->layer5->getPosition().y)));
}
