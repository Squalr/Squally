#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Amelia : public NpcBase
{
public:
	static Amelia* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAmelia;

private:
	Amelia(ValueMap* initProperties);
	~Amelia();
};
