#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Aspen : public NpcBase
{
public:
	static Aspen * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAspen;

private:
	Aspen(ValueMap* initProperties);
	~Aspen();
};
