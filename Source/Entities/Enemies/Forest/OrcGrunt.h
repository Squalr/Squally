#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class OrcGrunt : public Enemy
{
public:
	static OrcGrunt * create();

	static const std::string KeyEnemyOrcGrunt;

private:
	OrcGrunt();
	~OrcGrunt();
};
