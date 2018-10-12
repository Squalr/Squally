#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Rupert : public NpcBase
{
public:
	static Rupert * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcRupert;

private:
	Rupert(ValueMap* initProperties);
	~Rupert();
};
