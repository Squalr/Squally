////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Irmik : public NpcBase
{
public:
	static Irmik* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyIrmik;

private:
	Irmik(cocos2d::ValueMap& initProperties);
	~Irmik();
};
