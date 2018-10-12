#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Pan : public NpcBase
{
public:
	static Pan * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcPan;

private:
	Pan(ValueMap* initProperties);
	~Pan();
};
