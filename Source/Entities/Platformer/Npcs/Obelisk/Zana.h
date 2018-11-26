#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Zana : public NpcBase
{
public:
	static Zana* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcZana;

private:
	Zana(ValueMap* initProperties);
	~Zana();
};
