#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class PrincessOpal : public NpcBase
{
public:
	static PrincessOpal * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyPrincessOpal;

private:
	PrincessOpal(ValueMap* initProperties);
	~PrincessOpal();
};
