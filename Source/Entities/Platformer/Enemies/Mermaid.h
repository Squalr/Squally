////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Mermaid : public PlatformerEnemy
{
public:
	static Mermaid* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMermaid;

private:
	Mermaid(cocos2d::ValueMap* initProperties);
	~Mermaid();
};
