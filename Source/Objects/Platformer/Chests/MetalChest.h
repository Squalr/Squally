#pragma once

#include "Objects/Platformer/Chests/ChestBase.h"

using namespace cocos2d;

class CollisionObject;
class InteractMenu;
class MinMaxPool;

class MetalChest : public ChestBase
{
public:
	static MetalChest* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyMetalChest;

protected:
	MetalChest(cocos2d::ValueMap& properties);
	virtual ~MetalChest();

private:
	typedef ChestBase super;
};
