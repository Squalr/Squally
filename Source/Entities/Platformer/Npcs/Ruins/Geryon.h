#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Geryon : public NpcBase
{
public:
	static Geryon* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcGeryon;

private:
	Geryon(ValueMap* initProperties);
	~Geryon();
};
