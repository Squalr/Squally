#include "CavernSpider.h"

CavernSpider* CavernSpider::create()
{
	CavernSpider* instance = new CavernSpider();

	instance->autorelease();

	return instance;
}

CavernSpider::CavernSpider() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

CavernSpider::~CavernSpider()
{
}
