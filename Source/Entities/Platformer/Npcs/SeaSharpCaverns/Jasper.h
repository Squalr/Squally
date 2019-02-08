////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Jasper : public NpcBase
{
public:
	static Jasper* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyJasper;

private:
	Jasper(cocos2d::ValueMap& initProperties);
	~Jasper();
};
