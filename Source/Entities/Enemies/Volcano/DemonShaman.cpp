#include "DemonShaman.h"

const std::string DemonShaman::KeyEnemyDemonShaman = "demon_shaman";

DemonShaman* DemonShaman::create()
{
	DemonShaman* instance = new DemonShaman();

	instance->autorelease();

	return instance;
}

DemonShaman::DemonShaman() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonShaman_Animations,
	false,
	Size(212.0f, 280.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonShaman::~DemonShaman()
{
}
