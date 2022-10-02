#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolCVGeneric : public CurrencyPool
{
public:
	static CurrencyPoolCVGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolCVGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolCVGeneric();

private:
	typedef CurrencyPool super;
};
