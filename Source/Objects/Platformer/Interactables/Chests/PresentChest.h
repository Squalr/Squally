#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

class MinMaxPool;

class PresentChest : public ChestBase
{
public:
	static PresentChest* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	PresentChest(cocos2d::ValueMap& properties);
	virtual ~PresentChest();

private:
	typedef ChestBase super;
};
