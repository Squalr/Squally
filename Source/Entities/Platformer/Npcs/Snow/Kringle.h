#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Kringle : public NpcBase
{
public:
	static Kringle * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcKringle;

private:
	Kringle(ValueMap* initProperties);
	~Kringle();
};
