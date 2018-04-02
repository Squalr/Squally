#include "SmallBotSpider.h"

SmallBotSpider* SmallBotSpider::create()
{
	SmallBotSpider* instance = new SmallBotSpider();

	instance->autorelease();

	return instance;
}

SmallBotSpider::SmallBotSpider() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SmallBotSpider::~SmallBotSpider()
{
}
