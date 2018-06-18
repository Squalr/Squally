#include "FrostDragon.h"

const std::string FrostDragon::KeyEnemyFrostDragon = "frost_dragon";

FrostDragon* FrostDragon::create()
{
	FrostDragon* instance = new FrostDragon();

	instance->autorelease();

	return instance;
}

FrostDragon::FrostDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_FrostDragon_Animations,
	false,
	Size(720.0f, 356.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

FrostDragon::~FrostDragon()
{
}
