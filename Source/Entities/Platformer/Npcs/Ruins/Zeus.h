#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Zeus : public NpcBase
{
public:
	static Zeus* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcZeus;

private:
	Zeus(ValueMap* initProperties);
	~Zeus();
};
