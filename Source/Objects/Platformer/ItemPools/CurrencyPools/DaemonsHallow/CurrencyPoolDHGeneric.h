#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolDHGeneric : public CurrencyPool
{
public:
	static CurrencyPoolDHGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolDHGeneric(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolDHGeneric();

private:
	typedef CurrencyPool super;
};
