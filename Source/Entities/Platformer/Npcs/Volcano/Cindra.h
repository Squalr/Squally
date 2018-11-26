#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Cindra : public NpcBase
{
public:
	static Cindra* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcCindra;

private:
	Cindra(ValueMap* initProperties);
	~Cindra();
};
