////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Zelina : public NpcBase
{
public:
	static Zelina* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyZelina;

private:
	Zelina(cocos2d::ValueMap* initProperties);
	~Zelina();
};
