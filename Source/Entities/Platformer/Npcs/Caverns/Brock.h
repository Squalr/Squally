#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Brock : public NpcBase
{
public:
	static Brock* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcBrock;

private:
	Brock(ValueMap* initProperties);
	~Brock();
};
