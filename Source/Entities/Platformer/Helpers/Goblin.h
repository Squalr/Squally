////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Goblin : public PlatformerEntity
{
public:
	static Goblin* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyGoblin;

private:
	Goblin(cocos2d::ValueMap* initProperties);
	~Goblin();

	void onEnter() override;
};
