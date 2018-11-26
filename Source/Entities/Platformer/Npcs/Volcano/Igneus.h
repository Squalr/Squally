#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Igneus : public NpcBase
{
public:
	static Igneus* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcIgneus;

private:
	Igneus(ValueMap* initProperties);
	~Igneus();
};
