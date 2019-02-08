////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class AnubisPup : public PlatformerEnemy
{
public:
	static AnubisPup* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyAnubisPup;

private:
	AnubisPup(cocos2d::ValueMap& initProperties);
	~AnubisPup();
};
