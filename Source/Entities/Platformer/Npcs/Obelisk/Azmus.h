#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Azmus : public NpcBase
{
public:
	static Azmus* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAzmus;

private:
	Azmus(ValueMap* initProperties);
	~Azmus();
};
