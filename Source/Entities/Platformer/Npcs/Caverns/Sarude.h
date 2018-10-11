#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Sarude : public NpcBase
{
public:
	static Sarude * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySarude;

private:
	Sarude(ValueMap* initProperties);
	~Sarude();
};
