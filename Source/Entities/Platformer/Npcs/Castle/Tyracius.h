#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Tyracius : public NpcBase
{
public:
	static Tyracius* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcTyracius;

private:
	Tyracius(ValueMap* initProperties);
	~Tyracius();
};
