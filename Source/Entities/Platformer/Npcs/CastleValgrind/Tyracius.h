////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Tyracius : public NpcBase
{
public:
	static Tyracius* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyTyracius;

private:
	Tyracius(cocos2d::ValueMap* initProperties);
	~Tyracius();
};
