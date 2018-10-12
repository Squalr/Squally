#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Poseidon : public NpcBase
{
public:
	static Poseidon * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcPoseidon;

private:
	Poseidon(ValueMap* initProperties);
	~Poseidon();
};
