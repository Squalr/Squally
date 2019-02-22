#include "Inventory.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/InventoryEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const int Inventory::InfiniteCapacity = -1;
const std::string Inventory::SaveKeyCapacity = "capacity";
const std::string Inventory::SaveKeyItems = "items";

Inventory::Inventory(std::string saveKey, int capacity)
{
	this->saveKey = saveKey;
	this->capacity = capacity;
	this->items = std::vector<Item*>();
}

Inventory::~Inventory()
{
}

void Inventory::onEnter()
{
	super::onEnter();
}

void Inventory::initializeListeners()
{
	super::initializeListeners();
}

const ValueMap& Inventory::serialize()
{
	ValueMap saveData = ValueMap();
	ValueMap itemData = ValueMap();

	for (auto it = this->items.begin(); it != this->items.end(); it++)
	{
		itemData[(*it)->getSerializationKey()] = (Value((*it)->serialize()));
	}

	saveData[Inventory::SaveKeyCapacity] = Value(this->capacity);
	saveData[Inventory::SaveKeyItems] = itemData;

	return saveData;
}

void Inventory::deserialize(const ValueMap& valueMap)
{
	this->capacity = GameUtils::getKeyOrDefault(valueMap, Inventory::SaveKeyCapacity, Value(Inventory::InfiniteCapacity)).asInt();
	ValueMap itemData = GameUtils::getKeyOrDefault(valueMap, Inventory::SaveKeyItems, Value(ValueMap())).asValueMap();

	for (auto it = itemData.begin(); it != itemData.end(); it++)
	{
		InventoryEvents::TriggerRequestItemDeserialization(InventoryEvents::RequestItemDeserializationArgs(it->first, [=](Item* item)
		{
			this->forceInsert(item);
		}));
	}
}

void Inventory::save()
{
	if (!this->saveKey.empty())
	{
		SaveManager::saveProfileData(this->saveKey, Value(this->serialize()));
	}
}

void Inventory::load()
{
	if (!this->saveKey.empty())
	{
		this->deserialize(SaveManager::getGlobalData(this->saveKey).asValueMap());
	}
}

std::vector<Item*> Inventory::getItems()
{
	return this->items;
}

int Inventory::getCapacity()
{
	return this->capacity;
}

void Inventory::tryRemove(Item* item, std::function<void(Item*)> onRemove, std::function<void(Item*)> onRemoveFailed)
{
	if (item == nullptr || std::find(this->items.begin(), this->items.end(), item) == this->items.end())
	{
		if (onRemoveFailed != nullptr)
		{
			onRemoveFailed(item);
		}

		return;
	}

	this->items.erase(std::remove(this->items.begin(), this->items.end(), item), this->items.end());
	this->save();
}

void Inventory::tryInsert(Item* item, std::function<void(Item*)> onInsert, std::function<void(Item*)> onInsertFailed)
{
	if (this->capacity == Inventory::InfiniteCapacity || this->items.size() < this->capacity)
	{
		this->items.push_back(item);

		if (onInsert != nullptr)
		{
			this->save();
			onInsert(item);
		}
	}
	else
	{
		if (onInsertFailed != nullptr)
		{
			onInsertFailed(item);
		}
	}
}

void Inventory::forceInsert(Item* item)
{
	this->items.push_back(item);
	this->save();
}

void Inventory::tryTransact(Inventory* other, Item* item, Item* otherItem, std::function<void(Item*, Item*)> onTransact, std::function<void(Item*, Item*)> onTransactFailed)
{
	// Input checking
	if (other == nullptr || item == nullptr || otherItem == nullptr)
	{
		if (onTransactFailed != nullptr)
		{
			onTransactFailed(item, otherItem);
		}

		return;
	}

	// Check if items exist in the inventories
	if (std::find(this->items.begin(), this->items.end(), item) == this->items.end() ||
		std::find(other->items.begin(), other->items.end(), otherItem) == this->items.end())
	{
		if (onTransactFailed != nullptr)
		{
			onTransactFailed(item, otherItem);
		}

		return;
	}

	// Remove items with no safety checking, no reason it should fail at this stage
	other->tryRemove(otherItem, nullptr, nullptr);
	this->tryRemove(item, nullptr, nullptr);

	// Transact, again without safety checks
	other->tryInsert(item, nullptr, nullptr);
	this->tryInsert(otherItem, nullptr, nullptr);
}

void Inventory::moveItem(Item* item, int destinationIndex, std::function<void(Item*)> onMove, std::function<void(Item*)> onMoveFailed)
{
	// TODO: Do we even support indicies?

	// Just fail for now
	if (onMoveFailed != nullptr)
	{
		onMoveFailed(item);

		return;
	}

	this->save();
}
