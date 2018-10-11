#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Mabel : public NpcBase
{
public:
	static Mabel * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMabel;

private:
	Mabel(ValueMap* initProperties);
	~Mabel();
};
