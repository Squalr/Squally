#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Thurstan : public NpcBase
{
public:
	static Thurstan* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcThurstan;

private:
	Thurstan(ValueMap* initProperties);
	~Thurstan();
};
