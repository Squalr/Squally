#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Alder : public NpcBase
{
public:
	static Alder * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyAlder;

private:
	Alder(ValueMap* initProperties);
	~Alder();
};
