#include "BlackWidow.h"

BlackWidow* BlackWidow::create()
{
	BlackWidow* instance = new BlackWidow();

	instance->autorelease();

	return instance;
}

BlackWidow::BlackWidow() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_BlackWidow_Animation,
	"BlackWidow",
	false,
	Size(1024.0f, 960.0f),
	0.20f,
	Vec2(0.0f, -480.0f))
{
}

BlackWidow::~BlackWidow()
{
}
