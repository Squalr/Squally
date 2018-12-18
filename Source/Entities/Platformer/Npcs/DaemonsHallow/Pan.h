////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Pan : public NpcBase
{
public:
	static Pan* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPan;

private:
	Pan(cocos2d::ValueMap* initProperties);
	~Pan();
};
