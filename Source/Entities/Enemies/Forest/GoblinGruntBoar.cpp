#include "GoblinGruntBoar.h"

const std::string GoblinGruntBoar::KeyEnemyGoblinGruntBoar = "goblin_grunt_boar";

GoblinGruntBoar* GoblinGruntBoar::deserialize(ValueMap* initProperties)
{
	GoblinGruntBoar* instance = new GoblinGruntBoar(initProperties);

	instance->autorelease();

	return instance;
}

GoblinGruntBoar::GoblinGruntBoar(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_GoblinGruntBoar_Animations,
	false,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinGruntBoar::~GoblinGruntBoar()
{
}
