////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Alder : public NpcBase
{
public:
	static Alder* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAlder;

private:
	Alder(cocos2d::ValueMap* initProperties);
	~Alder();
};
