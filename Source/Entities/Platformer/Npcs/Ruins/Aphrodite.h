#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Aphrodite : public NpcBase
{
public:
	static Aphrodite* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAphrodite;

private:
	Aphrodite(ValueMap* initProperties);
	~Aphrodite();
};
