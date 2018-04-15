#include "BlueGoblin.h"

BlueGoblin* BlueGoblin::create()
{
	BlueGoblin* instance = new BlueGoblin();

	instance->autorelease();

	return instance;
}

BlueGoblin::BlueGoblin() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BlueGoblin::~BlueGoblin()
{
}
