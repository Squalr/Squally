#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

class MinMaxPool;

class EgyptianChest : public ChestBase
{
public:
	static EgyptianChest* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EgyptianChest(cocos2d::ValueMap& properties);
	virtual ~EgyptianChest();

private:
	typedef ChestBase super;
};
