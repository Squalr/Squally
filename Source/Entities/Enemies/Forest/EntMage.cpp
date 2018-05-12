#include "EntMage.h"

EntMage* EntMage::create()
{
	EntMage* instance = new EntMage();

	instance->autorelease();

	return instance;
}

EntMage::EntMage() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_EntMage_Animations,
	false,
	Size(512.0f, 820.0f),
	0.3f,
	Vec2(24.0f, -410.0f))
{
}

EntMage::~EntMage()
{
}
