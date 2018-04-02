#include "CavernSpider.h"

CavernSpider* CavernSpider::create()
{
	CavernSpider* instance = new CavernSpider();

	instance->autorelease();

	return instance;
}

CavernSpider::CavernSpider() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

CavernSpider::~CavernSpider()
{
}
