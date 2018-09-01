#include "Smoke.h"

const std::string Smoke::ScheduleKeySpawnSmoke = "SCHEDULE_SPAWN_SMOKE";

Smoke* Smoke::create(Node* followTarget)
{
	Smoke* instance = new Smoke(followTarget);

	instance->autorelease();

	return instance;
}

Smoke::Smoke(Node* followTarget)
{
	this->follow = followTarget;
	this->smokeSprite = Sprite::create(Resources::Cutscenes_NeonCity_FlyingCars_Smoke_0000);

	this->smokeAnimation = Animation::create();
	this->smokeAnimation->retain();

	auto shipFrames = GameUtils::getAllAnimationFiles(Resources::Cutscenes_NeonCity_FlyingCars_Smoke_0000);

	for (auto it = shipFrames.begin(); it != shipFrames.end(); it++)
	{
		this->smokeAnimation->addSpriteFrameWithFileName(*it);
	}

	this->smokeSprite->setOpacity(0);
	this->smokeAnimation->setDelayPerUnit(0.15f);

	this->addChild(this->smokeSprite);
}

Smoke::~Smoke()
{
	this->smokeAnimation->release();
}

void Smoke::onEnter()
{
	Node::onEnter();

	this->schedule([=](float dt)
	{
		this->setPosition(this->follow->getPosition());
		this->smokeSprite->runAction(Sequence::create(FadeTo::create(0.0f, 255), DelayTime::create(0.1f), Animate::create(this->smokeAnimation), FadeTo::create(0.0f, 0), nullptr));
	}, 2.0f, CC_REPEAT_FOREVER, RandomHelper::random_real(0.25f, 2.0f), Smoke::ScheduleKeySpawnSmoke);
}
