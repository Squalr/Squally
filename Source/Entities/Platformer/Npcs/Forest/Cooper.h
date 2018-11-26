#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Cooper : public NpcBase
{
public:
	static Cooper* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcCooper;

private:
	Cooper(ValueMap* initProperties);
	~Cooper();
};
