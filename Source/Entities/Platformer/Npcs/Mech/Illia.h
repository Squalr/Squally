#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Illia : public NpcBase
{
public:
	static Illia * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcIllia;

private:
	Illia(ValueMap* initProperties);
	~Illia();
};
