#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Ogre : public PlatformerEnemy
{
public:
	static Ogre * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyOgre;

private:
	Ogre(ValueMap* initProperties);
	~Ogre();
};
