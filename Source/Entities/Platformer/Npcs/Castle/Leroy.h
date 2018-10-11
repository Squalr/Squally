#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Leroy : public NpcBase
{
public:
	static Leroy * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyLeroy;

private:
	Leroy(ValueMap* initProperties);
	~Leroy();
};
