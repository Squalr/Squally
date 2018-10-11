#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Mildred : public NpcBase
{
public:
	static Mildred * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMildred;

private:
	Mildred(ValueMap* initProperties);
	~Mildred();
};
