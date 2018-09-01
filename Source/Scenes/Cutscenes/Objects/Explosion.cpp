#include "Explosion.h"

Explosion* Explosion::create(Vec2 speed)
{
	Explosion* instance = new Explosion(speed);

	instance->autorelease();

	return instance;
}

Explosion::Explosion(Vec2 speed)
{
	this->flySpeed = speed;
	this->carSprite = nullptr;

	if (this->carSprite != nullptr)
	{
		if (this->flySpeed.x < 0.0f)
		{
			this->carSprite->setFlippedX(true);
		}

		this->addChild(this->carSprite);
	}
}

Explosion::~Explosion()
{
}

void Explosion::onEnter()
{
	Node::onEnter();

	this->scheduleUpdate();
}

void Explosion::update(float dt)
{
	Node::update(dt);

	this->carSprite->setPosition(this->carSprite->getPosition() + dt * this->flySpeed);
}
