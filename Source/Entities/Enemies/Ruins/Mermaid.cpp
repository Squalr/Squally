#include "Mermaid.h"

const std::string Mermaid::KeyEnemyMermaid = "mermaid";

Mermaid* Mermaid::create()
{
	Mermaid* instance = new Mermaid();

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_Mermaid_Animations,
	false,
	Size(172.0f, 296.0f),
	0.8f,
	Vec2(0.0f, -140.0f))
{
	// this->animationNode->setFlippedX(true);
}

Mermaid::~Mermaid()
{
}
