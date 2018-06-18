#include "BlackWidow.h"

const std::string BlackWidow::KeyEnemyBlackWidow = "black_widow";

BlackWidow* BlackWidow::create()
{
	BlackWidow* instance = new BlackWidow();

	instance->autorelease();

	return instance;
}

BlackWidow::BlackWidow() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_BlackWidow_Animation,
	false,
	Size(1280.0f, 920.0f),
	0.20f,
	Vec2(-112.0f, -396.0f))
{
}

BlackWidow::~BlackWidow()
{
}
