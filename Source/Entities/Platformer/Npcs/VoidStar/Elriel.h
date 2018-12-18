////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Elriel : public NpcBase
{
public:
	static Elriel* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyElriel;

private:
	Elriel(cocos2d::ValueMap* initProperties);
	~Elriel();
};
