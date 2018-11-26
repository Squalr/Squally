#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Raven : public NpcBase
{
public:
	static Raven* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcRaven;

private:
	Raven(ValueMap* initProperties);
	~Raven();
};
