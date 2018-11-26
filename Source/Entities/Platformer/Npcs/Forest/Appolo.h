#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Appolo : public NpcBase
{
public:
	static Appolo* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAppolo;

private:
	Appolo(ValueMap* initProperties);
	~Appolo();
};
