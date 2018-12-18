////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Mara : public NpcBase
{
public:
	static Mara* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMara;

private:
	Mara(cocos2d::ValueMap* initProperties);
	~Mara();
};
