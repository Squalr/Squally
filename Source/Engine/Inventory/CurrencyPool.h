#pragma once

#include "Engine/Maps/GameObject.h"

class Currency;

class CurrencyPool : public GameObject
{
public:
	struct CurrencyData
	{
		Currency* currency = nullptr;
		int minCount = 0;
		int maxCount = 0;

		CurrencyData() { }
		CurrencyData(Currency* currency, int minCount, int maxCount)
			: currency(currency), minCount(minCount), maxCount(maxCount) { }
	};

	void addCurrencyToPool(CurrencyData currency);
	std::vector<Currency*> getRandomCurrencyFromPool();

protected:
	CurrencyPool(const cocos2d::ValueMap& properties, std::string poolName = "");
	CurrencyPool(std::string poolName = "");
	virtual ~CurrencyPool();

private:
	typedef GameObject super;

	std::string poolName;
	std::vector<CurrencyData> currencies;
};
