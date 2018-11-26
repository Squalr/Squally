#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Theldar : public NpcBase
{
public:
	static Theldar* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcTheldar;

private:
	Theldar(ValueMap* initProperties);
	~Theldar();
};
