#include "Mermaid.h"

Mermaid* Mermaid::create()
{
	Mermaid* instance = new Mermaid();

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Mermaid::~Mermaid()
{
}
