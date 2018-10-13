#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Aster : public NpcBase
{
public:
	static Aster * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAster;

private:
	Aster(ValueMap* initProperties);
	~Aster();
};
