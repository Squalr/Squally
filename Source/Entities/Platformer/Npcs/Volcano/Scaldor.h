#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Scaldor : public NpcBase
{
public:
	static Scaldor * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcScaldor;

private:
	Scaldor(ValueMap* initProperties);
	~Scaldor();
};
