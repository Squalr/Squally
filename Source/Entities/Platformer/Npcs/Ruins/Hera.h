#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Hera : public NpcBase
{
public:
	static Hera* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcHera;

private:
	Hera(ValueMap* initProperties);
	~Hera();
};
