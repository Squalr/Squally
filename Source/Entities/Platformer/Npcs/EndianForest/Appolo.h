////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Appolo : public NpcBase
{
public:
	static Appolo* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyAppolo;

private:
	Appolo(cocos2d::ValueMap& initProperties);
	~Appolo();
};
