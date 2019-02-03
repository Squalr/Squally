////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Robot.h"

#include "Resources/EntityResources.h"

const std::string Robot::MapKeyRobot = "robot";

Robot* Robot::deserialize(cocos2d::ValueMap* initProperties)
{
	Robot* instance = new Robot(initProperties);

	instance->autorelease();

	return instance;
}

Robot::Robot(cocos2d::ValueMap* initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_Robot_Animations,
	EntityResources::Helpers_Robot_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(224.0f, 440.0f),
	0.3f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Robot::~Robot()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////
