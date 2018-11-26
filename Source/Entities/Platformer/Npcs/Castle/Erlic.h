#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Erlic : public NpcBase
{
public:
	static Erlic* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcErlic;

private:
	Erlic(ValueMap* initProperties);
	~Erlic();
};
