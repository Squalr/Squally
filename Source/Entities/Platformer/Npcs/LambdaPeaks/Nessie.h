////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Nessie : public NpcBase
{
public:
	static Nessie* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyNessie;

private:
	Nessie(cocos2d::ValueMap* initProperties);
	~Nessie();
};
