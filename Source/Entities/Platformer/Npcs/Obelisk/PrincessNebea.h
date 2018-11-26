#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class PrincessNebea : public NpcBase
{
public:
	static PrincessNebea* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcPrincessNebea;

private:
	PrincessNebea(ValueMap* initProperties);
	~PrincessNebea();
};
