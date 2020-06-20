#pragma once

#include "Objects/Platformer/Rewards/RewardPool.h"

class RewardPoolHera : public RewardPool
{
public:
	static RewardPoolHera* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	RewardPoolHera(cocos2d::ValueMap& properties);
	virtual ~RewardPoolHera();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef RewardPool super;
};
