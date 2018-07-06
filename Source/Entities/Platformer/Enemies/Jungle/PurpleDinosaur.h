#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class PurpleDinosaur : public PlatformerEnemy
{
public:
	static PurpleDinosaur * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyPurpleDinosaur;

private:
	PurpleDinosaur(ValueMap* initProperties);
	~PurpleDinosaur();
};
