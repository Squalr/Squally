#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Atreus : public NpcBase
{
public:
	static Atreus * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAtreus;

private:
	Atreus(ValueMap* initProperties);
	~Atreus();
};
