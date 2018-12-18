////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#include "Gecko.h"

const std::string Gecko::MapKeyGecko = "gecko";

Gecko* Gecko::deserialize(ValueMap* initProperties)
{
	Gecko* instance = new Gecko(initProperties);

	instance->autorelease();

	return instance;
}

Gecko::Gecko(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Helpers_Gecko_Animations,
	PlatformerCollisionType::FriendlyNpc,
	Size(296.0f, 356.0f),
	1.0,
	Vec2(0.0f, 0.0f))
{
}

Gecko::~Gecko()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
