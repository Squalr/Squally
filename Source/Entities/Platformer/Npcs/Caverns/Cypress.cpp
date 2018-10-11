#include "Cypress.h"

const std::string Cypress::KeyEnemyCypress = "cypress";

Cypress* Cypress::deserialize(ValueMap* initProperties)
{
	Cypress* instance = new Cypress(initProperties);

	instance->autorelease();

	return instance;
}

Cypress::Cypress(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Cypress_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Cypress::~Cypress()
{
}
