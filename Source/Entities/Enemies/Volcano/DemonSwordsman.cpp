#include "DemonSwordsman.h"

const std::string DemonSwordsman::KeyEnemyDemonSwordsman = "demon_swordsman";

DemonSwordsman* DemonSwordsman::deserialize(ValueMap* initProperties)
{
	DemonSwordsman* instance = new DemonSwordsman(initProperties);

	instance->autorelease();

	return instance;
}

DemonSwordsman::DemonSwordsman(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_DemonSwordsman_Animations,
	false,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonSwordsman::~DemonSwordsman()
{
}
