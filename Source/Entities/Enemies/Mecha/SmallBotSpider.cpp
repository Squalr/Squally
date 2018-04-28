#include "SmallBotSpider.h"

SmallBotSpider* SmallBotSpider::create()
{
	SmallBotSpider* instance = new SmallBotSpider();

	instance->autorelease();

	return instance;
}

SmallBotSpider::SmallBotSpider() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

SmallBotSpider::~SmallBotSpider()
{
}
