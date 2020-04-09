#pragma once

#include "Engine/Inventory/DropPool.h"

class RewardPoolLiana : public DropPool
{
public:
	static RewardPoolLiana* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	RewardPoolLiana(cocos2d::ValueMap& properties);
	virtual ~RewardPoolLiana();

private:
	typedef DropPool super;
};
