#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Cypress : public NpcBase
{
public:
	static Cypress* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcCypress;

private:
	Cypress(ValueMap* initProperties);
	~Cypress();
};
