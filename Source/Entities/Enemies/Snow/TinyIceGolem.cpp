#include "TinyIceGolem.h"

const std::string TinyIceGolem::KeyEnemyTinyIceGolem = "tiny_ice_golem";

TinyIceGolem* TinyIceGolem::deserialize(ValueMap* initProperties)
{
	TinyIceGolem* instance = new TinyIceGolem(initProperties);

	instance->autorelease();

	return instance;
}

TinyIceGolem::TinyIceGolem(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_TinyIceGolem_Animations,
	false,
	Size(980.0f, 1360.0f),
	0.17f,
	Vec2(0.0f, -680.0f))
{
}

TinyIceGolem::~TinyIceGolem()
{
}
