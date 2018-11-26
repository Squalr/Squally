#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Lucifer : public NpcBase
{
public:
	static Lucifer* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcLucifer;

private:
	Lucifer(ValueMap* initProperties);
	~Lucifer();
};
