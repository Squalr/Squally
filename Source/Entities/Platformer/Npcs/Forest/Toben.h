#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Toben : public NpcBase
{
public:
	static Toben* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcToben;

private:
	Toben(ValueMap* initProperties);
	~Toben();
};
