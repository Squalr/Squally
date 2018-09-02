#include "Explosion.h"

Explosion* Explosion::create()
{
	Explosion* instance = new Explosion();

	instance->autorelease();

	return instance;
}

Explosion::Explosion()
{
	this->setCascadeOpacityEnabled(true);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->explosion = LayerColor::create(Color4B(255, 255, 255, 196), visibleSize.width, visibleSize.height);

	this->addChild(this->explosion);
}

Explosion::~Explosion()
{
}

void Explosion::onEnter()
{
	Node::onEnter();

	const float flashSpeed = 0.015f;

	this->runAction(Sequence::create(
		Repeat::create(Sequence::create(
			FadeTo::create(flashSpeed, 0),
			FadeTo::create(flashSpeed, 255),
			nullptr
		), 10),
		FadeTo::create(flashSpeed, 0),
		nullptr
	));
}
