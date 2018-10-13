#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Bodom : public NpcBase
{
public:
	static Bodom * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcBodom;

private:
	Bodom(ValueMap* initProperties);
	~Bodom();
};
