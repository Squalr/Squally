#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class TinyIceGolem : public Enemy
{
public:
	static TinyIceGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyTinyIceGolem;

private:
	TinyIceGolem(ValueMap* initProperties);
	~TinyIceGolem();
};
