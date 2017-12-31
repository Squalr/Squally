#include "JungleBackground.h"

JungleBackground* JungleBackground::create()
{
	JungleBackground* newBackground = new JungleBackground();

	newBackground->autorelease();

	return newBackground;
}

JungleBackground::JungleBackground()
{
	this->background = Sprite::create(Resources::Ingame_Background_Jungle_Background);
	this->layer6 = InfiniteParallaxNode::create(Resources::Ingame_Background_Jungle_Layer_6);
	this->layer5 = InfiniteParallaxNode::create(Resources::Ingame_Background_Jungle_Layer_5);
	this->layer4 = InfiniteParallaxNode::create(Resources::Ingame_Background_Jungle_Layer_4);
	this->layer2 = InfiniteParallaxNode::create(Resources::Ingame_Background_Jungle_Layer_2);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->layer6->setPosition(Vec2(this->layer6->getContentSize().width / 2, visibleSize.height / 2));
	this->layer5->setPosition(Vec2(this->layer5->getContentSize().width / 2, visibleSize.height / 2));
	this->layer4->setPosition(Vec2(this->layer4->getContentSize().width / 2, 0.0f));
	this->layer2->setPosition(Vec2(this->layer2->getContentSize().width / 2, visibleSize.height / 2));

	this->addChild(this->background);
	this->addChild(this->layer6);
	this->addChild(this->layer5);
	this->addChild(this->layer4);
	this->addChild(this->layer2);

	this->scheduleUpdate();
}

JungleBackground::~JungleBackground()
{
}

void JungleBackground::update(float dt)
{
	Layer::update(dt);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float widthOffset = Director::getInstance()->getVisibleSize().width / 2;
	float playerXOffset = Player::position.x;

	this->layer6->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 80.0f, this->layer6->getPosition().y)));
	this->layer5->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 60.0f, this->layer5->getPosition().y)));
	this->layer4->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 40.0f, this->layer4->getPosition().y)));
	this->layer2->runAction(MoveTo::create(0.0f, Vec2(-playerXOffset / 20.0f, this->layer2->getPosition().y)));
}
