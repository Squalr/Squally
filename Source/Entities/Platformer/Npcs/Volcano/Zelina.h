#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Zelina : public NpcBase
{
public:
	static Zelina* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcZelina;

private:
	Zelina(ValueMap* initProperties);
	~Zelina();
};
