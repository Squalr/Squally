#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Radon : public NpcBase
{
public:
	static Radon* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcRadon;

private:
	Radon(ValueMap* initProperties);
	~Radon();
};
