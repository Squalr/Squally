#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Shen : public NpcBase
{
public:
	static Shen* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcShen;

private:
	Shen(ValueMap* initProperties);
	~Shen();
};
