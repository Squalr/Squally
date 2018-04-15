#include "SmallBotSpider.h"

SmallBotSpider* SmallBotSpider::create()
{
	SmallBotSpider* instance = new SmallBotSpider();

	instance->autorelease();

	return instance;
}

SmallBotSpider::SmallBotSpider() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

SmallBotSpider::~SmallBotSpider()
{
}
