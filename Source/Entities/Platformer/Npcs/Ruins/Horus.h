#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Horus : public NpcBase
{
public:
	static Horus* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcHorus;

private:
	Horus(ValueMap* initProperties);
	~Horus();
};
