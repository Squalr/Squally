#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Ursula : public NpcBase
{
public:
	static Ursula* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcUrsula;

private:
	Ursula(ValueMap* initProperties);
	~Ursula();
};
