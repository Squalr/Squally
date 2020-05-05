#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

using namespace cocos2d;

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
