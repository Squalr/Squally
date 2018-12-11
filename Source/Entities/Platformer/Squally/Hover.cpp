#include "Hover.h"

Hover* Hover::create(PlatformerEntity* initParent)
{
	Hover* hover = new Hover(initParent);

	hover->autorelease();

	return hover;
}

Hover::Hover(PlatformerEntity* initParent) : CollisionObject(
	nullptr,
	PhysicsBody::createBox(Size(initParent->getSize().width, Hover::hoverHeight), PhysicsMaterial(0.0f, 0.0f, 0.0f)),
	(int)PlatformerCollisionType::Force,
	true,
	false)
{
	this->parent = initParent;

	Size parentSize = this->parent->getSize();

	this->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->setPosition(0, -parentSize.height / 2);
	this->setContentSize(Size(0, Hover::hoverHeight));

	FiniteTimeAction* bounceY1 = EaseSineInOut::create(ScaleTo::create(3.0f, 1.0f, 0.25f));
	FiniteTimeAction* bounceY2 = EaseSineInOut::create(ScaleTo::create(3.0f, 1.0f, 1.0f));

	// this->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
}

Hover::~Hover()
{
}

void Hover::setHeight(float height)
{

}

void Hover::setMaxHeight(float maxHeight)
{

}

void Hover::setFloatDelta(float delta)
{

}

void Hover::update(float dt)
{
	CollisionObject::update(dt);

	// Keep hover node underneath parent
	this->setPosition(0, -this->parent->getSize().height / 2 + 1.0f);
	this->setVelocity(this->parent->getVelocity());
}
