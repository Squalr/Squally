#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolVSHexus : public CurrencyPool
{
public:
	static CurrencyPoolVSHexus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolVSHexus(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolVSHexus();

private:
	typedef CurrencyPool super;
};
