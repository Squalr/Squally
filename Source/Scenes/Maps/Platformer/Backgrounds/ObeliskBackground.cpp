#include "ObeliskBackground.h"

const std::string ObeliskBackground::MapKeyBackgroundLayerObelisk = "obelisk";

ObeliskBackground* ObeliskBackground::create(ValueMap* properties, std::string name)
{
	ObeliskBackground* instance = new ObeliskBackground(properties, name);

	instance->autorelease();

	return instance;
}

ObeliskBackground::ObeliskBackground(ValueMap* properties, std::string name) : BackgroundBase(properties, name)
{
	this->background = Sprite::create(BackgroundResources::Platformer_Obelisk_sky);
	this->background2 = InfiniteParallaxNode::create(BackgroundResources::Platformer_Obelisk_background_plan_2);
	this->background3 = InfiniteParallaxNode::create(BackgroundResources::Platformer_Obelisk_background_plan_1);
	this->midground1 = InfiniteParallaxNode::create(BackgroundResources::Platformer_Obelisk_middleground_1);
	this->midground2 = InfiniteParallaxNode::create(BackgroundResources::Platformer_Obelisk_middleground_3);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->background2->setPosition(Vec2(this->background2->getContentSize().width / 2, visibleSize.height / 2));
	this->background3->setPosition(Vec2(this->background3->getContentSize().width / 2, visibleSize.height / 2));
	this->midground1->setPosition(Vec2(this->midground1->getContentSize().width / 2, 0.0f));
	this->midground2->setPosition(Vec2(this->midground2->getContentSize().width / 2, visibleSize.height / 2));

	this->addChild(this->background);
	this->addChild(this->background2);
	this->addChild(this->background3);
	//this->addChild(this->midground1);
	this->addChild(this->midground2);

	this->scheduleUpdate();
}

ObeliskBackground::~ObeliskBackground()
{
}

void ObeliskBackground::update(float dt)
{
	BackgroundBase::update(dt);

	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->background2->runAction(MoveTo::create(0.0f, Vec2(-cameraPosition.x / 80.0f, this->background2->getPosition().y)));
	this->background3->runAction(MoveTo::create(0.0f, Vec2(-cameraPosition.x / 60.0f, this->background3->getPosition().y)));
	//this->midground1->runAction(MoveTo::create(0.0f, Vec2(-cameraPosition.x / 40.0f, this->midground1->getPosition().y)));
	this->midground2->runAction(MoveTo::create(0.0f, Vec2(-cameraPosition.x / 20.0f, this->midground2->getPosition().y)));
}
