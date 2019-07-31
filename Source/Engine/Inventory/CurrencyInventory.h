#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, cocos2d::Value> ValueMap;
}

class CurrencyInventory : public SmartNode
{
public:
	static CurrencyInventory* create(std::string saveKey = "");

	int getCurrencyCount(std::string currencyKey);
	void removeCurrency(std::string currencyKey, int count);
	void addCurrency(std::string currencyKey, int count);

protected:
	CurrencyInventory(std::string saveKey = "");
	virtual ~CurrencyInventory();

	void onEnter() override;
	void initializeListeners() override;

	void deserialize(const cocos2d::ValueMap& valueMap);

private:
	typedef SmartNode super;

	void save();
	void load();
	
	cocos2d::ValueMap currencyMap;

	std::string saveKey;
};
