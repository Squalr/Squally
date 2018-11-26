#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Drak : public NpcBase
{
public:
	static Drak* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcDrak;

private:
	Drak(ValueMap* initProperties);
	~Drak();
};
