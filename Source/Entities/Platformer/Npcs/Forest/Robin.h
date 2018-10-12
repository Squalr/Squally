#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Robin : public NpcBase
{
public:
	static Robin * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcRobin;

private:
	Robin(ValueMap* initProperties);
	~Robin();
};
