#include "TikiGolem.h"

const std::string TikiGolem::KeyEnemyTikiGolem = "tiki_golem";

TikiGolem* TikiGolem::deserialize(ValueMap* initProperties)
{
	TikiGolem* instance = new TikiGolem(initProperties);

	instance->autorelease();

	return instance;
}

TikiGolem::TikiGolem(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Jungle_TikiGolem_Animations,
	false,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, -112.0f))
{
}

TikiGolem::~TikiGolem()
{
}
