#pragma once

#include "Engine/Inventory/DropPool.h"

class RewardPoolElriel : public DropPool
{
public:
	static RewardPoolElriel* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	RewardPoolElriel(cocos2d::ValueMap& properties);
	virtual ~RewardPoolElriel();

private:
	typedef DropPool super;
};
