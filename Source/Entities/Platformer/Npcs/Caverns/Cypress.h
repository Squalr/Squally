#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Cypress : public NpcBase
{
public:
	static Cypress * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyCypress;

private:
	Cypress(ValueMap* initProperties);
	~Cypress();
};
