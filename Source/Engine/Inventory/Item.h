#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class CurrencyInventory;
class LocalizedString;

class Item : public SmartNode
{
public:
	virtual Item* clone() = 0;
	virtual std::string getItemName() = 0;
	virtual LocalizedString* getString() = 0;
	virtual std::string getIconResource() = 0;
	virtual std::string getSerializationKey() = 0;
	virtual cocos2d::ValueMap serialize();
	int getCount();
	int getStackSize();

	static const int MaxStack;

protected:
	Item(CurrencyInventory* cost, int stackSize = 1);
	virtual ~Item();
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	int count;
	int stackSize;
	CurrencyInventory* cost;
};
