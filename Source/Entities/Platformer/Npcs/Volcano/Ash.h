#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Ash : public NpcBase
{
public:
	static Ash* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAsh;

private:
	Ash(ValueMap* initProperties);
	~Ash();
};
