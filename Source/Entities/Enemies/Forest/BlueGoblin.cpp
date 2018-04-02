#include "BlueGoblin.h"

BlueGoblin* BlueGoblin::create()
{
	BlueGoblin* instance = new BlueGoblin();

	instance->autorelease();

	return instance;
}

BlueGoblin::BlueGoblin() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BlueGoblin::~BlueGoblin()
{
}
