#pragma once

#include "Objects/Platformer/Collectables/SpawnPools/SpawnPool.h"

class SpawnPoolEF : public SpawnPool
{
public:
	static SpawnPoolEF* create(cocos2d::ValueMap& properties);
	
	static const std::string MapKey;

protected:
	SpawnPoolEF(cocos2d::ValueMap& properties);
	virtual ~SpawnPoolEF();

	Collectable* spawnCollectable() override;

private:
	typedef SpawnPool super;
};
