#include "GoblinShaman.h"

const std::string GoblinShaman::KeyEnemyGoblinShaman = "goblin_shaman";

GoblinShaman* GoblinShaman::create()
{
	GoblinShaman* instance = new GoblinShaman();

	instance->autorelease();

	return instance;
}

GoblinShaman::GoblinShaman() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_GoblinShaman_Animations,
	false,
	Size(96.0f, 204.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinShaman::~GoblinShaman()
{
}
