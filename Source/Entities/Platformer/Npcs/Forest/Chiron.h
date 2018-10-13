#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Chiron : public NpcBase
{
public:
	static Chiron * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcChiron;

private:
	Chiron(ValueMap* initProperties);
	~Chiron();
};
