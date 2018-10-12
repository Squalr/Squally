#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Elriel : public NpcBase
{
public:
	static Elriel * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcElriel;

private:
	Elriel(ValueMap* initProperties);
	~Elriel();
};
