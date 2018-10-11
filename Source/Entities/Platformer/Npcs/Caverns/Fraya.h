#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Fraya : public NpcBase
{
public:
	static Fraya * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyFraya;

private:
	Fraya(ValueMap* initProperties);
	~Fraya();
};
