#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Ysara : public NpcBase
{
public:
	static Ysara* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcYsara;

private:
	Ysara(ValueMap* initProperties);
	~Ysara();
};
