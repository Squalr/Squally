#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Viper : public NpcBase
{
public:
	static Viper * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcViper;

private:
	Viper(ValueMap* initProperties);
	~Viper();
};
