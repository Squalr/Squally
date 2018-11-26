#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Jasper : public NpcBase
{
public:
	static Jasper* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcJasper;

private:
	Jasper(ValueMap* initProperties);
	~Jasper();
};
