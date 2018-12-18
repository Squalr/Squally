////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Cypress : public NpcBase
{
public:
	static Cypress* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyCypress;

private:
	Cypress(cocos2d::ValueMap* initProperties);
	~Cypress();
};
