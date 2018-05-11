#include "DemonSwordsman.h"

DemonSwordsman* DemonSwordsman::create()
{
	DemonSwordsman* instance = new DemonSwordsman();

	instance->autorelease();

	return instance;
}

DemonSwordsman::DemonSwordsman() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonSwordsman_Animations,
	false)
{
}

DemonSwordsman::~DemonSwordsman()
{
}
