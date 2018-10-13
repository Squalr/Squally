#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Blackbeard : public NpcBase
{
public:
	static Blackbeard * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcBlackbeard;

private:
	Blackbeard(ValueMap* initProperties);
	~Blackbeard();
};
