#pragma once

#include "Engine/Maps/GameObject.h"

class Item;
class ItemChance;
class Inventory;

class CurrencyPool : public GameObject
{
public:
	struct Currency
	{
		std::string identifier;
		int minCount;
		int maxCount;
		int count;

		Currency() : identifier(""), minCount(0), maxCount(0), count(0) { }
		Currency(std::string identifier, int minCount, int maxCount) : identifier(identifier), minCount(minCount), maxCount(maxCount), count(maxCount) { }
	};

	void addCurrencyToPool(Currency currency);
	std::vector<Currency> getRandomCurrencyFromPool();

protected:
	CurrencyPool(const cocos2d::ValueMap& properties, std::string poolName = "");
	CurrencyPool(std::string poolName = "");
	virtual ~CurrencyPool();

private:
	typedef GameObject super;

	std::string poolName;
	std::vector<Currency> currencies;
};
