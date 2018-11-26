#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Juniper : public NpcBase
{
public:
	static Juniper* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcJuniper;

private:
	Juniper(ValueMap* initProperties);
	~Juniper();
};
