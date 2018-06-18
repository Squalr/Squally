#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class AnubisTiny : public Enemy
{
public:
	static AnubisTiny * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyAnubisTiny;

private:
	AnubisTiny(ValueMap* initProperties);
	~AnubisTiny();
};
