#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolBPGeneric : public CurrencyPool
{
public:
	static CurrencyPoolBPGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolBPGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolBPGeneric();

private:
	typedef CurrencyPool super;
};
