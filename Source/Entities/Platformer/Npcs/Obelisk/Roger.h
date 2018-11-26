#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Roger : public NpcBase
{
public:
	static Roger* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcRoger;

private:
	Roger(ValueMap* initProperties);
	~Roger();
};
