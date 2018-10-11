#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Merlin : public NpcBase
{
public:
	static Merlin * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMerlin;

private:
	Merlin(ValueMap* initProperties);
	~Merlin();
};
