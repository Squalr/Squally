#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class PrincessMittens : public NpcBase
{
public:
	static PrincessMittens* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcPrincessMittens;

private:
	PrincessMittens(ValueMap* initProperties);
	~PrincessMittens();
};
