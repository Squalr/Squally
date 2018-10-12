#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Ares : public NpcBase
{
public:
	static Ares * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAres;

private:
	Ares(ValueMap* initProperties);
	~Ares();
};
