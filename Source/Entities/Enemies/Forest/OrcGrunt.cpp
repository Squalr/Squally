#include "OrcGrunt.h"

OrcGrunt* OrcGrunt::create()
{
	OrcGrunt* instance = new OrcGrunt();

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

OrcGrunt::~OrcGrunt()
{
}
