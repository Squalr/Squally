#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class PurpleDinosaur : public Enemy
{
public:
	static PurpleDinosaur * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyPurpleDinosaur;

private:
	PurpleDinosaur(ValueMap* initProperties);
	~PurpleDinosaur();
};
