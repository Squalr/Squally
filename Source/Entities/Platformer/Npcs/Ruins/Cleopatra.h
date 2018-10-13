#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Cleopatra : public NpcBase
{
public:
	static Cleopatra * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcCleopatra;

private:
	Cleopatra(ValueMap* initProperties);
	~Cleopatra();
};
