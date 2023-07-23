#pragma once

#include "Engine/Inventory/DropPool.h"

class RewardPoolLycan : public DropPool
{
public:
	static RewardPoolLycan* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	RewardPoolLycan(cocos2d::ValueMap& properties);
	virtual ~RewardPoolLycan();

private:
	typedef DropPool super;
};
