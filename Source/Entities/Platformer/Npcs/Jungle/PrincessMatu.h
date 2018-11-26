#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class PrincessMatu : public NpcBase
{
public:
	static PrincessMatu* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcPrincessMatu;

private:
	PrincessMatu(ValueMap* initProperties);
	~PrincessMatu();
};
