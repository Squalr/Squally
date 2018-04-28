#include "Mermaid.h"

Mermaid* Mermaid::create()
{
	Mermaid* instance = new Mermaid();

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Mermaid::~Mermaid()
{
}
