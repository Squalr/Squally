////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Polyphemus : public NpcBase
{
public:
	static Polyphemus* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPolyphemus;

private:
	Polyphemus(cocos2d::ValueMap* initProperties);
	~Polyphemus();
};
