#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Minos : public NpcBase
{
public:
	static Minos* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcMinos;

private:
	Minos(ValueMap* initProperties);
	~Minos();
};
