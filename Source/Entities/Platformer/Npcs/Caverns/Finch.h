#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Finch : public NpcBase
{
public:
	static Finch * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcFinch;

private:
	Finch(ValueMap* initProperties);
	~Finch();
};
