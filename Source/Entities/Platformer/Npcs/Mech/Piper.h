#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Piper : public NpcBase
{
public:
	static Piper* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcPiper;

private:
	Piper(ValueMap* initProperties);
	~Piper();
};
