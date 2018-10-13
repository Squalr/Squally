#include "Mermaid.h"

const std::string Mermaid::MapKeyEnemyMermaid = "mermaid";

Mermaid* Mermaid::deserialize(ValueMap* initProperties)
{
	Mermaid* instance = new Mermaid(initProperties);

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Enemies_Mermaid_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(172.0f, 296.0f),
	0.8f,
	Vec2(0.0f, -140.0f))
{
	// this->animationNode->setFlippedX(true);
}

Mermaid::~Mermaid()
{
}
