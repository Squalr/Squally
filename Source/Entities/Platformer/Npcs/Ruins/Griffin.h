#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Griffin : public NpcBase
{
public:
	static Griffin * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcGriffin;

private:
	Griffin(ValueMap* initProperties);
	~Griffin();
};
