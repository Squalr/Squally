#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Fraya : public NpcBase
{
public:
	static Fraya* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcFraya;

private:
	Fraya(ValueMap* initProperties);
	~Fraya();
};
