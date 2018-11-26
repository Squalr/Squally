#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Brine : public NpcBase
{
public:
	static Brine* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcBrine;

private:
	Brine(ValueMap* initProperties);
	~Brine();
};
