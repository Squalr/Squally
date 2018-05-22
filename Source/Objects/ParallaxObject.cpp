#include "ParallaxObject.h"

ParallaxObject* ParallaxObject::create(Node* parallaxChild, Vec2 parallaxPosition, Vec2 parallaxSpeed)
{
	ParallaxObject* parallaxObject = new ParallaxObject(parallaxChild, parallaxPosition, parallaxSpeed);

	parallaxObject->autorelease();

	return parallaxObject;
}

ParallaxObject::ParallaxObject(Node* parallaxChild, Vec2 parallaxPosition, Vec2 parallaxSpeed)
{
	this->initialPosition = parallaxPosition;
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
	Vec2 cameraPosition = LevelCamera::getInstance()->getCameraPosition();

	this->child->setPosition(this->initialPosition + Vec2(
		(cameraPosition.x + visibleSize.width / 2 - this->initialPosition.x) * this->speed.x,
		(cameraPosition.y + visibleSize.height / 2 - this->initialPosition.y) * this->speed.y
	));
}
