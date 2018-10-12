#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Jingles : public NpcBase
{
public:
	static Jingles * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcJingles;

private:
	Jingles(ValueMap* initProperties);
	~Jingles();
};
