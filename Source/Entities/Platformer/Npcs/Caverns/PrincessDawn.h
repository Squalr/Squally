#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class PrincessDawn : public NpcBase
{
public:
	static PrincessDawn * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcPrincessDawn;

private:
	PrincessDawn(ValueMap* initProperties);
	~PrincessDawn();
};
