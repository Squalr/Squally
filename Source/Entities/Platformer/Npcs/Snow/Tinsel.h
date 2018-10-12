#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Tinsel : public NpcBase
{
public:
	static Tinsel * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcTinsel;

private:
	Tinsel(ValueMap* initProperties);
	~Tinsel();
};
