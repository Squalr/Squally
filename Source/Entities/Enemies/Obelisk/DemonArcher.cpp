#include "DemonArcher.h"

const std::string DemonArcher::KeyEnemyDemonArcher = "demon_archer";

DemonArcher* DemonArcher::deserialize(ValueMap* initProperties)
{
	DemonArcher* instance = new DemonArcher(initProperties);

	instance->autorelease();

	return instance;
}

DemonArcher::DemonArcher(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Obelisk_DemonArcher_Animations,
	false,
	Size(196.0f, 348.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonArcher::~DemonArcher()
{
}
