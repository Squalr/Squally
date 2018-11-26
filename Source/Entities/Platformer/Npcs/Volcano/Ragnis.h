#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Ragnis : public NpcBase
{
public:
	static Ragnis* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcRagnis;

private:
	Ragnis(ValueMap* initProperties);
	~Ragnis();
};
