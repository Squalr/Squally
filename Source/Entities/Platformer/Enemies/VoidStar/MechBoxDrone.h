////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class MechBoxDrone : public PlatformerEnemy
{
public:
	static MechBoxDrone* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMechBoxDrone;

private:
	MechBoxDrone(cocos2d::ValueMap& initProperties);
	~MechBoxDrone();
};
