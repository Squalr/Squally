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
	bool hasItemOfType()
	{
		for (auto next : this->items)
		{
			if (dynamic_cast<T*>(next) != nullptr)
			{
				return true;
			}
		}

		return false;
	};

	bool hasItemOfName(std::string itemName);

	template<class T>
	std::vector<T*> getItemsOfType()
	{
		std::vector<T*> foundItems;

		for (auto next : this->items)
		{
			if (dynamic_cast<T*>(next) != nullptr)
			{
				foundItems.push_back(dynamic_cast<T*>(next));
			}
		}

		return foundItems;
	};

	template<class T>
	T* getItemOfType()
	{
		for (auto next : this->items)
		{
			if (dynamic_cast<T*>(next) != nullptr)
			{
				return dynamic_cast<T*>(next);
			}
		}

		return nullptr;
	};

	int getCapacity();
	void tryRemove(Item* item, std::function<void(Item*)> onRemove = nullptr, std::function<void(Item*)> onRemoveFailed = nullptr, bool doSave = true);
	void tryInsert(Item* item, std::function<void(Item*)> onInsert = nullptr, std::function<void(Item*)> onInsertFailed = nullptr, bool doSave = true);
	void forceInsert(Item* item, bool doSave = true);
	void tryTransact(Inventory* other, Item* item, Item* otherItem = nullptr, std::function<void(Item*, Item*)> onTransact = nullptr, std::function<void(Item*, Item*)> onTransactFailed = nullptr, bool doSave = true);
	void moveItem(Item* item, int destinationIndex, std::function<void(Item*)> onMove = nullptr, std::function<void(Item*)> onMoveFailed = nullptr, bool doSave = true);
	void save();
	std::string getSaveKey();
	
protected:
	Inventory(std::string saveKey = "", int capacity = Inventory::InfiniteCapacity);
	virtual ~Inventory();
	void onEnter() override;
	void initializeListeners() override;

	void load();
	cocos2d::ValueMap serialize();
	void deserialize(const cocos2d::ValueMap& valueMap);
	void clearItems();

	std::vector<Item*> items;
	std::set<std::string> itemLookup;
	int capacity;

	static const int InfiniteCapacity;

private:
	typedef SmartNode super;

	void rebuildLookupTable();
	bool canInsertItemIfUnique(Item* item);

	cocos2d::Node* itemsNode;

	std::string saveKey;

	static const std::string SaveKeyCapacity;
	static const std::string SaveKeyItems;
};
