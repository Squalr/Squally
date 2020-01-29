#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolEFGeneric : public CurrencyPool
{
public:
	static CurrencyPoolEFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolEFGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolEFGeneric();

private:
	typedef CurrencyPool super;
};
