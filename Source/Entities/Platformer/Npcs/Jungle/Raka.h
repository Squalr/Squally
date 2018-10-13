#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Raka : public NpcBase
{
public:
	static Raka * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcRaka;

private:
	Raka(ValueMap* initProperties);
	~Raka();
};
