#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolFFHexus : public CurrencyPool
{
public:
	static CurrencyPoolFFHexus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolFFHexus(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolFFHexus();

private:
	typedef CurrencyPool super;
};
