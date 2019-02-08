////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class MechGuard : public PlatformerEnemy
{
public:
	static MechGuard* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMechGuard;

private:
	MechGuard(cocos2d::ValueMap& initProperties);
	~MechGuard();
};
