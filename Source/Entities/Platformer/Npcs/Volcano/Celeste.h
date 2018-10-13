#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Celeste : public NpcBase
{
public:
	static Celeste * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcCeleste;

private:
	Celeste(ValueMap* initProperties);
	~Celeste();
};
