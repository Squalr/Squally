#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Athena : public NpcBase
{
public:
	static Athena * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAthena;

private:
	Athena(ValueMap* initProperties);
	~Athena();
};
