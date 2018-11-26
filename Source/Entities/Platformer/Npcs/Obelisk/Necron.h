#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Necron : public NpcBase
{
public:
	static Necron* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcNecron;

private:
	Necron(ValueMap* initProperties);
	~Necron();
};
