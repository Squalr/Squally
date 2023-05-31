#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolURHexus : public CurrencyPool
{
public:
	static CurrencyPoolURHexus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolURHexus(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolURHexus();

private:
	typedef CurrencyPool super;
};
