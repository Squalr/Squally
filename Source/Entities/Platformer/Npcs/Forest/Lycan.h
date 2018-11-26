#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Lycan : public NpcBase
{
public:
	static Lycan* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcLycan;

private:
	Lycan(ValueMap* initProperties);
	~Lycan();
};
