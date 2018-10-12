#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Manticore : public NpcBase
{
public:
	static Manticore * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcManticore;

private:
	Manticore(ValueMap* initProperties);
	~Manticore();
};
