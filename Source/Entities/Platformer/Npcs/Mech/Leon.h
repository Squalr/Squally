#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Leon : public NpcBase
{
public:
	static Leon * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcLeon;

private:
	Leon(ValueMap* initProperties);
	~Leon();
};
