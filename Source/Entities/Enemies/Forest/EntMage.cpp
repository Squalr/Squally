#include "EntMage.h"

EntMage* EntMage::create()
{
	EntMage* instance = new EntMage();

	instance->autorelease();

	return instance;
}

EntMage::EntMage() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_EntMage_Animations,
	false)
{
}

EntMage::~EntMage()
{
}
