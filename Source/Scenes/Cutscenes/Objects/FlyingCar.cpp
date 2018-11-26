#include "FlyingCar.h"

const std::string FlyingCar::ScheduleKeySputterSmoke = "SCHEDULE_SPUTTER_SMOKE";
const float FlyingCar::gravity = 192.0f;

FlyingCar* FlyingCar::create(CarType carType, Vec2 speed, float groundHeight)
{
	FlyingCar* instance = new FlyingCar(carType, speed, groundHeight);

	instance->autorelease();

	return instance;
}

FlyingCar::FlyingCar(CarType carType, Vec2 speed, float groundHeight)
{
	this->height = groundHeight;
	this->isCrashing = false;
	this->flySpeed = speed;
	this->smoke = nullptr;
	this->carSprite = nullptr;

	switch (carType)
	{
		case CarType::Junker:
		{
			this->carSprite = Sprite::create(CutsceneResources::NeonCity_FlyingCars_Junker_0000);
			Animation* animation = Animation::create();
			auto shipFrames = GameUtils::getAllAnimationFiles(CutsceneResources::NeonCity_FlyingCars_Junker_0000);

			for (auto it = shipFrames.begin(); it != shipFrames.end(); it++)
			{
				animation->addSpriteFrameWithFileName(*it);
			}

			animation->setDelayPerUnit(0.2f);
			this->carSprite->runAction(RepeatForever::create(Sequence::create(Animate::create(animation), nullptr)));

			this->smoke = Smoke::create(this->carSprite);
			break;
		}
		case CarType::Viper:
		{
			this->carSprite = Sprite::create(CutsceneResources::NeonCity_FlyingCars_Viper_0000);
			Animation* animation = Animation::create();
			auto shipFrames = GameUtils::getAllAnimationFiles(CutsceneResources::NeonCity_FlyingCars_Viper_0000);

			for (auto it = shipFrames.begin(); it != shipFrames.end(); it++)
			{
				animation->addSpriteFrameWithFileName(*it);
			}

			animation->setDelayPerUnit(0.2f);
			this->carSprite->runAction(RepeatForever::create(Sequence::create(Animate::create(animation), nullptr)));

			this->smoke = Smoke::create(this->carSprite);
			break;
		}
		case CarType::Propeller:
		{
			this->carSprite = Sprite::create(CutsceneResources::NeonCity_FlyingCars_Propeller_0000);
			Animation* animation = Animation::create();
			auto shipFrames = GameUtils::getAllAnimationFiles(CutsceneResources::NeonCity_FlyingCars_Propeller_0000);

			for (auto it = shipFrames.begin(); it != shipFrames.end(); it++)
			{
				animation->addSpriteFrameWithFileName(*it);
			}

			animation->setDelayPerUnit(0.2f);
			this->carSprite->runAction(RepeatForever::create(Sequence::create(Animate::create(animation), nullptr)));
			break;
		}
	}

	if (this->smoke != nullptr)
	{
		this->addChild(this->smoke);
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

void FlyingCar::crash()
{
	if (this->smoke != nullptr)
	{
		this->smoke->stopFollow();
	}

	const float sputterDuration = 0.35f;
	const int sputterCount = 3;

	this->isCrashing = true;

	// Create smoke sputters
	this->schedule([=](float dt)
	{
		Smoke* smoke = Smoke::create(this->carSprite);
		smoke->stopFollow();

		this->addChild(smoke);
	}, sputterDuration, sputterCount, 0.0f, FlyingCar::ScheduleKeySputterSmoke);

	// Kinematics to figure out time to impact
	float fallHeight = this->getPositionY() - this->height;
	float crashTime = (2.0f * fallHeight) / (std::sqrt(2.0f * FlyingCar::gravity * fallHeight));

	// Fall & explode
	this->runAction(Sequence::create(
		DelayTime::create(crashTime),
		CallFunc::create([=]() {
			this->explode();
		}),
		DelayTime::create(0.2f),
		CallFunc::create([=]() {
			this->carSprite->runAction(FadeTo::create(0.25f, 0));
		}),
		CallFunc::create([=]()
		{
			this->unscheduleUpdate();
		}),
		nullptr
	));
}

void FlyingCar::explode()
{
	Explosion* explosion = Explosion::create();

	// A little bit of magic to add the explosion in such a way that it covers the screen exactly
	this->getParent()->addChild(explosion);
	GameUtils::changeParent(explosion, this, true);
}

void FlyingCar::onEnter()
{
	Node::onEnter();

	this->scheduleUpdate();
}

void FlyingCar::update(float dt)
{

	Node::update(dt);

	if (this->isCrashing)
	{
		this->flySpeed.y -= FlyingCar::gravity * dt;
	}

	this->carSprite->setPosition(this->carSprite->getPosition() + dt * this->flySpeed);
}
