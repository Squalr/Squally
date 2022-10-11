#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolVSGeneric : public CurrencyPool
{
public:
	static CurrencyPoolVSGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolVSGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolVSGeneric();

private:
	typedef CurrencyPool super;
};
