#include "Jack.h"

const std::string Jack::KeyEnemyJack = "jack";

Jack* Jack::deserialize(ValueMap* initProperties)
{
	Jack* instance = new Jack(initProperties);

	instance->autorelease();

	return instance;
}

Jack::Jack(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Castle_Jack_Animations,
	false,
	Size(432.0f, 768.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
}

Jack::~Jack()
{
}
