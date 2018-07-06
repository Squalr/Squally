#include "ParallaxObject.h"

ParallaxObject* ParallaxObject::create(ValueMap* initProperties, Node* parallaxChild, Vec2 parallaxSpeed)
{
	ParallaxObject* instance = new ParallaxObject(initProperties, parallaxChild,parallaxSpeed);

	instance->autorelease();

	return instance;
}

ParallaxObject::ParallaxObject(ValueMap* initProperties, Node* parallaxChild,Vec2 parallaxSpeed) : HackableObject(initProperties)
{
	this->speed = parallaxSpeed;
	this->child = parallaxChild;

	this->addChild(parallaxChild);

	this->scheduleUpdate();
}

ParallaxObject::~ParallaxObject()
{
}

void ParallaxObject::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	this->child->setPosition(Vec2(
		(cameraPosition.x + visibleSize.width / 2 - this->getPositionX()) * this->speed.x,
		(cameraPosition.y + visibleSize.height / 2 - this->getPositionY()) * this->speed.y
	));
}
