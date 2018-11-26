#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Johann : public NpcBase
{
public:
	static Johann* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcJohann;

private:
	Johann(ValueMap* initProperties);
	~Johann();
};
