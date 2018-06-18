#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinGruntBoar : public Enemy
{
public:
	static GoblinGruntBoar * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinGruntBoar;

private:
	GoblinGruntBoar(ValueMap* initProperties);
	~GoblinGruntBoar();
};
