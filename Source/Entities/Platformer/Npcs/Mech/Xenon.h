#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Xenon : public NpcBase
{
public:
	static Xenon* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcXenon;

private:
	Xenon(ValueMap* initProperties);
	~Xenon();
};
