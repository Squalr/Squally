#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Rusty : public NpcBase
{
public:
	static Rusty* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcRusty;

private:
	Rusty(ValueMap* initProperties);
	~Rusty();
};
