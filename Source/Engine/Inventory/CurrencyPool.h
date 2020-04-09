#pragma once

#include "Engine/Maps/GameObject.h"

class Currency;
class Item;
class ItemChance;
class Inventory;
class LocalizedString;

class CurrencyPool : public GameObject
{
public:
	struct CurrencyData
	{
		Currency* currency;
		int minCount;
		int maxCount;

		CurrencyData() : currency(nullptr), minCount(0), maxCount(0) { }
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
