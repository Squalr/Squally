////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Mermaid.h"

#include "Resources/EntityResources.h"

const std::string Mermaid::MapKeyMermaid = "mermaid";

Mermaid* Mermaid::deserialize(cocos2d::ValueMap* initProperties)
{
	Mermaid* instance = new Mermaid(initProperties);

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid(cocos2d::ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_Mermaid_Animations,
	PlatformerCollisionType::Enemy,
	cocos2d::Size(172.0f, 296.0f),
	0.8f,
	cocos2d::Vec2(0.0f, -140.0f),
	10,
	10)
{
}

Mermaid::~Mermaid()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
