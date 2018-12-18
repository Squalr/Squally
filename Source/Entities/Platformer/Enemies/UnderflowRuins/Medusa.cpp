////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Medusa.h"

#include "Resources/EntityResources.h"

const std::string Medusa::MapKeyMedusa = "medusa";

Medusa* Medusa::deserialize(cocos2d::ValueMap* initProperties)
{
	Medusa* instance = new Medusa(initProperties);

	instance->autorelease();

	return instance;
}

Medusa::Medusa(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_Medusa_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(224.0f, 304.0f),
	0.8f,
	cocos2d::Vec2(0.0f, 0.0f))
{
}

Medusa::~Medusa()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
