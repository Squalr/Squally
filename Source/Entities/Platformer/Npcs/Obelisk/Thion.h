#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Thion : public NpcBase
{
public:
	static Thion* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcThion;

private:
	Thion(ValueMap* initProperties);
	~Thion();
};
