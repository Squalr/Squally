#pragma once

#include "Objects/Platformer/Chests/ChestBase.h"

using namespace cocos2d;

class CollisionObject;
class InteractMenu;
class MinMaxPool;

class Chest : public ChestBase
{
public:
	static Chest* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Chest(cocos2d::ValueMap& properties);
	virtual ~Chest();

private:
	typedef ChestBase super;
};
