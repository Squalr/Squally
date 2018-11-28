#include "SnowBackground.h"

const std::string SnowBackground::MapKeyBackgroundLayerSnow = "snow";

SnowBackground* SnowBackground::create(ValueMap* properties, std::string name)
{
	SnowBackground* instance = new SnowBackground(properties, name);

	instance->autorelease();

	return instance;
}

SnowBackground::SnowBackground(ValueMap* properties, std::string name) : BackgroundBase(properties, name)
{
	this->background = Sprite::create(BackgroundResources::Platformer_Snow_snowmountains_bg);
	this->layer6 = InfiniteParallaxNode::create(BackgroundResources::Platformer_Snow_snowmountains_fg);
	this->layer5 = InfiniteParallaxNode::create(BackgroundResources::Platformer_Snow_snowmountains_acc);

	Size visibleSize = Director::getInstance()->getVisibleSize();

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
	BackgroundBase::update(dt);

	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->layer6->runAction(MoveTo::create(0.0f, Vec2(-cameraPosition.x / 80.0f, this->layer6->getPosition().y)));
	this->layer5->runAction(MoveTo::create(0.0f, Vec2(-cameraPosition.x / 60.0f, this->layer5->getPosition().y)));
}
