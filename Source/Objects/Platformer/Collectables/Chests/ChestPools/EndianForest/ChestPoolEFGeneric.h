#pragma once

#include "Objects/Platformer/Collectables/Chests/ChestPools/ChestPool.h"

class ChestPoolEFGeneric : public ChestPool
{
public:
	static ChestPoolEFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFGeneric(cocos2d::ValueMap& properties);
	~ChestPoolEFGeneric();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef ChestPool super;
};
