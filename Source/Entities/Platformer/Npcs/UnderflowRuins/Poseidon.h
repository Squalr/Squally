////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Poseidon : public NpcBase
{
public:
	static Poseidon* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPoseidon;

private:
	Poseidon(cocos2d::ValueMap* initProperties);
	~Poseidon();
};
