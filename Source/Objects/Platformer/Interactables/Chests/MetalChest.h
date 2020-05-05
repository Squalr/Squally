#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

using namespace cocos2d;

class MinMaxPool;

class MetalChest : public ChestBase
{
public:
	static MetalChest* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MetalChest(cocos2d::ValueMap& properties);
	virtual ~MetalChest();

private:
	typedef ChestBase super;
};
