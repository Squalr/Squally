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
	static Inventory* create(std::string saveKey = "", int capacity = Inventory::InfiniteCapacity);

	std::vector<Item*> getItems();

	template<class T>
	std::vector<T*> getItemsOfType()
	{
		std::vector<T*> foundItems;

		for (auto it = this->items.begin(); it != this->items.end(); it++)
		{
			if (dynamic_cast<T*>(*it) != nullptr)
			{
				foundItems.push_back(dynamic_cast<T*>(*it));
			}
		}

		return foundItems;
	};

	int getCapacity();
	void tryRemove(Item* item, std::function<void(Item*)> onRemove = nullptr, std::function<void(Item*)> onRemoveFailed = nullptr);
	void tryInsert(Item* item, std::function<void(Item*)> onInsert = nullptr, std::function<void(Item*)> onInsertFailed = nullptr);
	void forceInsert(Item* item);
	void tryTransact(Inventory* other, Item* item, Item* otherItem = nullptr, std::function<void(Item*, Item*)> onTransact = nullptr, std::function<void(Item*, Item*)> onTransactFailed = nullptr);
	void moveItem(Item* item, int destinationIndex, std::function<void(Item*)> onMove = nullptr, std::function<void(Item*)> onMoveFailed = nullptr);

protected:
	Inventory(std::string saveKey = "", int capacity = Inventory::InfiniteCapacity);
	virtual ~Inventory();
	void onEnter() override;
	void initializeListeners() override;

	void save();
	void load();
	cocos2d::ValueMap serialize();
	void deserialize(const cocos2d::ValueMap& valueMap);
	void clearItems();

	std::vector<Item*> items;
	int capacity;

	static const int InfiniteCapacity;

private:
	typedef SmartNode super;

	cocos2d::Node* itemsNode;

	std::string saveKey;

	static const std::string SaveKeyCapacity;
	static const std::string SaveKeyItems;
};
