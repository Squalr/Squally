////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Theldar : public NpcBase
{
public:
	static Theldar* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTheldar;

private:
	Theldar(cocos2d::ValueMap& initProperties);
	~Theldar();
};
