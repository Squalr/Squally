#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Polyphemus : public NpcBase
{
public:
	static Polyphemus * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcPolyphemus;

private:
	Polyphemus(ValueMap* initProperties);
	~Polyphemus();
};
