#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolDMGeneric : public CurrencyPool
{
public:
	static CurrencyPoolDMGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolDMGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolDMGeneric();

private:
	typedef CurrencyPool super;
};
