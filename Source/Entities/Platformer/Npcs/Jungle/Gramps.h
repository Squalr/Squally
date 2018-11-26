#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Gramps : public NpcBase
{
public:
	static Gramps* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcGramps;

private:
	Gramps(ValueMap* initProperties);
	~Gramps();
};
