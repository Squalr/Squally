#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolURGeneric : public CurrencyPool
{
public:
	static CurrencyPoolURGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolURGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolURGeneric();

private:
	typedef CurrencyPool super;
};
