#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Dudly : public NpcBase
{
public:
	static Dudly* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcDudly;

private:
	Dudly(ValueMap* initProperties);
	~Dudly();
};
