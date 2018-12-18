////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Abomination.h"

const std::string Abomination::MapKeyAbomination = "abomination";

Abomination* Abomination::deserialize(ValueMap* initProperties)
{
	Abomination* instance = new Abomination(initProperties);

	instance->autorelease();

	return instance;
}

Abomination::Abomination(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_Abomination_Animations,
	PlatformerCollisionType::Enemy,
	Size(296.0f, 356.0f),
	0.6,
	Vec2(0.0f, 0.0f))
{
}

Abomination::~Abomination()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
