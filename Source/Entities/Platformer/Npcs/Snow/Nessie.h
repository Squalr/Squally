#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Nessie : public NpcBase
{
public:
	static Nessie* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcNessie;

private:
	Nessie(ValueMap* initProperties);
	~Nessie();
};
