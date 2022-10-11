#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolLCGeneric : public CurrencyPool
{
public:
	static CurrencyPoolLCGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolLCGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolLCGeneric();

private:
	typedef CurrencyPool super;
};
