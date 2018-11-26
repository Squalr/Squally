#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Alder : public NpcBase
{
public:
	static Alder* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAlder;

private:
	Alder(ValueMap* initProperties);
	~Alder();
};
