#include "LavaGolem.h"

const std::string LavaGolem::KeyEnemyLavaGolem = "lava_golem";

LavaGolem* LavaGolem::deserialize(ValueMap* initProperties)
{
	LavaGolem* instance = new LavaGolem(initProperties);

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Volcano_LavaGolem_Animations,
	false,
	Size(980.0f, 1200.0f),
	0.17f,
	Vec2(0.0f, -600.0f))
{
}

LavaGolem::~LavaGolem()
{
}
