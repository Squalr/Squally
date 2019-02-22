#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, cocos2d::Value> ValueMap;
}

class Item;

class Inventory : public SmartNode
{
public:
	std::vector<Item*> getItems();
	int getCapacity();
	void tryRemove(Item* item, std::function<void(Item*)> onRemove, std::function<void(Item*)> onRemoveFailed);
	void tryInsert(Item* item, std::function<void(Item*)> onInsert, std::function<void(Item*)> onInsertFailed);
	void tryTransact(Inventory* other, Item* item, Item* otherItem, std::function<void(Item*, Item*)> onTransact, std::function<void(Item*, Item*)> onTransactFailed);
	void moveItem(Item* item, int destinationIndex, std::function<void(Item*)> onMove, std::function<void(Item*)> onMoveFailed);

protected:
	Inventory(std::string saveKey = "", int capacity = InfiniteCapacity);
	virtual ~Inventory();
	void onEnter() override;
	void initializeListeners() override;

	void save();
	void load();
	cocos2d::ValueMap serialize();
	void deserialize(cocos2d::ValueMap& valueMap);

	std::vector<Item*> items;
	int capacity;

	static const int InfiniteCapacity;

private:
	typedef SmartNode super;

	std::string saveKey;
};
