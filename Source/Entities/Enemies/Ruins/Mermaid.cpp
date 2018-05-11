#include "Mermaid.h"

Mermaid* Mermaid::create()
{
	Mermaid* instance = new Mermaid();

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_Mermaid_Animations,
	false,
	Size(378.0f, 378.0f),
	0.75f,
	Vec2(0.0f, -172.0f))
{
	this->animationNode->setFlippedX(true);
}

Mermaid::~Mermaid()
{
}
