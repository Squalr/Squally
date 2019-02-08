////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Minos : public NpcBase
{
public:
	static Minos* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMinos;

private:
	Minos(cocos2d::ValueMap& initProperties);
	~Minos();
};
