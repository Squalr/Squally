#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Mara : public NpcBase
{
public:
	static Mara * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcMara;

private:
	Mara(ValueMap* initProperties);
	~Mara();
};
