#pragma once

#include "Objects/Platformer/Collectables/SpawnPools/SpawnPool.h"

class SpawnPoolUR : public SpawnPool
{
public:
	static SpawnPoolUR* create(cocos2d::ValueMap& properties);
	
	static const std::string MapKey;

protected:
	SpawnPoolUR(cocos2d::ValueMap& properties);
	virtual ~SpawnPoolUR();

private:
	typedef SpawnPool super;
};
