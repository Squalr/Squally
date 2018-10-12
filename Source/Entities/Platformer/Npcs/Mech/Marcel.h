#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Marcel : public NpcBase
{
public:
	static Marcel * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcMarcel;

private:
	Marcel(ValueMap* initProperties);
	~Marcel();
};
