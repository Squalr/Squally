#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class QueenElise : public NpcBase
{
public:
	static QueenElise * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcQueenElise;

private:
	QueenElise(ValueMap* initProperties);
	~QueenElise();
};
