#include "Hover.h"

Hover* Hover::create(Entity* initParent)
{
	Hover* hover = new Hover(initParent);

	hover->autorelease();

	return hover;
}

Hover::Hover(Entity* initParent)
{
	this->parent = initParent;

	this->contactBeginCallback = nullptr;
	this->contactUpdateCallback = nullptr;
	this->contactEndCallback = nullptr;

	this->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->setPosition(0, -this->parent->getHeight() / 2);
	this->setContentSize(Size(0, Hover::hoverHeight));

	this->init(PhysicsBody::createBox(Size(this->parent->getWidth(), Hover::hoverHeight)), CategoryGroup::G_Force, true, false);

	FiniteTimeAction* bounceY1 = EaseSineInOut::create(ScaleTo::create(3.0f, 1.0f, 0.25f));
	FiniteTimeAction* bounceY2 = EaseSineInOut::create(ScaleTo::create(3.0f, 1.0f, 1.0f));

	this->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
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
	this->setPosition(0, -this->parent->getHeight() / 2 + 1.0f);
	this->setVelocity(this->parent->getVelocity());
}

void Hover::setContactBeginCallback(std::function<bool(CollisionData)> callback)
{
	this->contactBeginCallback = callback;
}

void Hover::setContactUpdateCallback(std::function<bool(CollisionData)> callback)
{
	this->contactUpdateCallback = callback;
}

void Hover::setContactEndCallback(std::function<bool(CollisionData)> callback)
{
	this->contactEndCallback = callback;
}

bool Hover::contactBegin(CollisionData data)
{
	if (this->contactBeginCallback != nullptr)
	{
		return this->contactBeginCallback(data);
	}

	return true;
}

bool Hover::contactUpdate(CollisionData data)
{
	if (this->contactUpdateCallback != nullptr)
	{
		return this->contactUpdateCallback(data);
	}

	return true;
}

bool Hover::contactEnd(CollisionData data)
{
	if (this->contactUpdateCallback != nullptr)
	{
		return this->contactEndCallback(data);
	}

	return true;
}
