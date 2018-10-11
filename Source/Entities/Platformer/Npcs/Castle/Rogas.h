#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Rogas : public NpcBase
{
public:
	static Rogas * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyRogas;

private:
	Rogas(ValueMap* initProperties);
	~Rogas();
};
