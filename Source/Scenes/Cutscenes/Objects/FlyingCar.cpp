#include "FlyingCar.h"

FlyingCar* FlyingCar::create(CarType carType, Vec2 speed)
{
	FlyingCar* instance = new FlyingCar(carType, speed);

	instance->autorelease();

	return instance;
}

FlyingCar::FlyingCar(CarType carType, Vec2 speed)
{
	this->flySpeed = speed;
	this->carSprite = nullptr;

	switch (carType)
	{
		case CarType::Junker:
		{
			this->carSprite = Sprite::create(Resources::Cutscenes_NeonCity_FlyingCars_Junker_0000);
			Animation* animation = Animation::create();
			auto shipFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_NeonCity_FlyingCars_Junker_0000);

			for (auto it = shipFrames.begin(); it != shipFrames.end(); it++)
			{
				animation->addSpriteFrameWithFileName(*it);
			}

			animation->setDelayPerUnit(0.2f);
			this->carSprite->runAction(RepeatForever::create(Sequence::create(Animate::create(animation), nullptr)));
			break;
		}
		case CarType::Viper:
		{
			this->carSprite = Sprite::create(Resources::Cutscenes_NeonCity_FlyingCars_Viper_0000);
			Animation* animation = Animation::create();
			auto shipFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_NeonCity_FlyingCars_Viper_0000);

			for (auto it = shipFrames.begin(); it != shipFrames.end(); it++)
			{
				animation->addSpriteFrameWithFileName(*it);
			}

			animation->setDelayPerUnit(0.2f);
			this->carSprite->runAction(RepeatForever::create(Sequence::create(Animate::create(animation), nullptr)));
			break;
		}
		case CarType::Propeller:
		{
			this->carSprite = Sprite::create(Resources::Cutscenes_NeonCity_FlyingCars_Propeller_0000);
			Animation* animation = Animation::create();
			auto shipFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_NeonCity_FlyingCars_Propeller_0000);

			for (auto it = shipFrames.begin(); it != shipFrames.end(); it++)
			{
				animation->addSpriteFrameWithFileName(*it);
			}

			animation->setDelayPerUnit(0.2f);
			this->carSprite->runAction(RepeatForever::create(Sequence::create(Animate::create(animation), nullptr)));
			break;
		}
	}

	if (this->carSprite != nullptr)
	{
		if (this->flySpeed.x < 0.0f)
		{
			this->carSprite->setFlippedX(true);
		}

		this->addChild(this->carSprite);
	}
}

FlyingCar::~FlyingCar()
{
}

void FlyingCar::onEnter()
{
	Node::onEnter();

	this->scheduleUpdate();
}

void FlyingCar::update(float dt)
{
	Node::update(dt);

	this->carSprite->setPosition(this->carSprite->getPosition() + dt * this->flySpeed);
}
