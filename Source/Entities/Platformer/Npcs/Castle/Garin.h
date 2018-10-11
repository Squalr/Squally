#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Garin : public NpcBase
{
public:
	static Garin * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGarin;

private:
	Garin(ValueMap* initProperties);
	~Garin();
};
