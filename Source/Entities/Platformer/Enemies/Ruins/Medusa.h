#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Medusa : public PlatformerEnemy
{
public:
	static Medusa * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMedusa;

private:
	Medusa(ValueMap* initProperties);
	~Medusa();
};
