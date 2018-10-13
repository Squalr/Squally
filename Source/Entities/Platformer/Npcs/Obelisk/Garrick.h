#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Garrick : public NpcBase
{
public:
	static Garrick * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcGarrick;

private:
	Garrick(ValueMap* initProperties);
	~Garrick();
};
