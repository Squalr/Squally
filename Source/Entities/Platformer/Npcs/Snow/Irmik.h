#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Irmik : public NpcBase
{
public:
	static Irmik * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcIrmik;

private:
	Irmik(ValueMap* initProperties);
	~Irmik();
};
