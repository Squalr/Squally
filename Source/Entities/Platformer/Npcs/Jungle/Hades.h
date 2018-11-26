#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Hades : public NpcBase
{
public:
	static Hades* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcHades;

private:
	Hades(ValueMap* initProperties);
	~Hades();
};
