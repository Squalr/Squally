#include "PurpleDinosaur.h"

const std::string PurpleDinosaur::KeyEnemyPurpleDinosaur = "purple_dinosaur";

PurpleDinosaur* PurpleDinosaur::deserialize(ValueMap* initProperties)
{
	PurpleDinosaur* instance = new PurpleDinosaur(initProperties);

	instance->autorelease();

	return instance;
}

PurpleDinosaur::PurpleDinosaur(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Enemies_PurpleDinosaur_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(412.0f, 388.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

PurpleDinosaur::~PurpleDinosaur()
{
}
