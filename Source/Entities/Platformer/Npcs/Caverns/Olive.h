#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Olive : public NpcBase
{
public:
	static Olive* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcOlive;

private:
	Olive(ValueMap* initProperties);
	~Olive();
};
