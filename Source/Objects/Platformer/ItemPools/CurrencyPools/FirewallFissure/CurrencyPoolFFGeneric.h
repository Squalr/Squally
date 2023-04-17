#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolFFGeneric : public CurrencyPool
{
public:
	static CurrencyPoolFFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolFFGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolFFGeneric();

private:
	typedef CurrencyPool super;
};
