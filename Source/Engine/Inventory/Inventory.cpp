#include "Inventory.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/InventoryEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const int Inventory::InfiniteCapacity = -1;
const std::string Inventory::SaveKeyCapacity = "capacity";
const std::string Inventory::SaveKeyItems = "items";

Inventory* Inventory::create(std::string saveKey, int capacity)
{
	Inventory* instance = new Inventory(saveKey, capacity);

	instance->autorelease();

	return instance;
}

Inventory::Inventory(std::string saveKey, int capacity)
{
	this->saveKey = saveKey;
	this->capacity = capacity;
	this->items = std::vector<Item*>();
	this->itemLookup = std::set<std::string>();
	this->itemsNode = Node::create();
	this->disableLookupTableRebuilding = false;

	this->load();

	this->addChild(this->itemsNode);
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(InventoryEvents::EventInventoryInstanceChangedPrefix + this->saveKey, [=](EventCustom* eventCustom)
	{
		InventoryEvents::InventoryInstanceChangedArgs* args = static_cast<InventoryEvents::InventoryInstanceChangedArgs*>(eventCustom->getData());
		
		if (args != nullptr && args->instance != this)
		{
			this->load();
		}
	}));
}

ValueMap Inventory::serialize()
{
	ValueMap saveData = ValueMap();
	ValueVector itemData = ValueVector();

	for (auto next : this->items)
	{
		itemData.push_back(Value(next->getSerializationKey()));
	}

	saveData[Inventory::SaveKeyCapacity] = Value(this->capacity);
	saveData[Inventory::SaveKeyItems] = itemData;

	return saveData;
}

void Inventory::deserialize(const ValueMap& valueMap)
{
	this->clearItems();

	this->capacity = GameUtils::getKeyOrDefault(valueMap, Inventory::SaveKeyCapacity, Value(Inventory::InfiniteCapacity)).asInt();
	ValueVector itemData = GameUtils::getKeyOrDefault(valueMap, Inventory::SaveKeyItems, Value(ValueVector())).asValueVector();

	this->disableLookupTableRebuilding = true;

	for (auto next : itemData)
	{
		InventoryEvents::TriggerRequestItemDeserialization(InventoryEvents::RequestItemDeserializationArgs(next.asString(), [=](Item* item)
		{
			this->forceInsert(item, false);
		}));
	}

	this->disableLookupTableRebuilding = false;
	this->rebuildLookupTable();
}

bool Inventory::hasItemOfName(std::string itemName)
{
	return this->itemLookup.find(itemName) != this->itemLookup.end();
}

void Inventory::clearItems()
{
	this->itemsNode->removeAllChildren();
	this->items.clear();
	this->itemLookup.clear();
}

void Inventory::save()
{
	if (!this->saveKey.empty())
	{
		SaveManager::SaveProfileData(this->saveKey, Value(this->serialize()));
		
		InventoryEvents::TriggerInventoryInstanceChanged(InventoryEvents::InventoryInstanceChangedArgs(this, this->saveKey));
	}
}

std::string Inventory::getSaveKey()
{
	return this->saveKey;
}

void Inventory::load()
{
	if (!this->saveKey.empty())
	{
		this->deserialize(SaveManager::GetProfileDataOrDefault(this->saveKey, Value(ValueMap())).asValueMap());
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

void Inventory::tryRemove(Item* item, std::function<void(Item*)> onRemove, std::function<void(Item*)> onRemoveFailed, bool doSave)
{
	if (item == nullptr)
	{
		if (onRemove != nullptr)
		{
			onRemove(nullptr);
		}

		return;
	}

	// Quick O(1) check using the set
	if (this->itemLookup.find(item->getItemName()) == this->itemLookup.end())
	{
		if (onRemoveFailed != nullptr)
		{
			onRemoveFailed(item);
		}

		return;
	}
	
	Item* returnItem = onRemove == nullptr ? nullptr : item->clone();

	this->removeChild(item);
	this->items.erase(std::remove(this->items.begin(), this->items.end(), item), this->items.end());

	if (doSave)
	{
		this->save();
	}
	
	this->rebuildLookupTable();

	if (onRemove != nullptr)
	{
		onRemove(returnItem);
	}
}

void Inventory::tryInsert(Item* item, std::function<void(Item*)> onInsert, std::function<void(Item*)> onInsertFailed, bool doSave)
{
	if (item != nullptr && this->canInsertItemIfUnique(item) && (this->capacity == Inventory::InfiniteCapacity || int(this->items.size()) < this->capacity))
	{
		this->itemsNode->addChild(item);
		this->items.push_back(item);

		if (onInsert != nullptr)
		{
			if (doSave)
			{
				this->save();
			}

			onInsert(item);
		}

		this->rebuildLookupTable();

		return;
	}
	else
	{
		if (onInsertFailed != nullptr)
		{
			onInsertFailed(item);
		}
	}
}

void Inventory::forceInsert(Item* item, bool doSave)
{
	if (item != nullptr)
	{
		this->itemsNode->addChild(item);
		this->items.push_back(item);

		if (doSave)
		{
			this->save();
		}

		this->rebuildLookupTable();
	}
}

void Inventory::tryTransact(Inventory* other, Item* item, Item* otherItem, std::function<void(Item*, Item*)> onTransact, std::function<void(Item*, Item*)> onTransactFailed, bool doSave)
{
	auto failTransaction = [=]()
	{
		if (onTransactFailed != nullptr)
		{
			onTransactFailed(item, otherItem);
		}
	};

	// Input checking
	if (other == nullptr || item == nullptr)
	{
		failTransaction();
		return;
	}

	// Check if items exist in the inventories
	if (std::find(this->items.begin(), this->items.end(), item) == this->items.end())
	{
		failTransaction();
		return;
	}

	int itemIndex = std::distance(this->items.begin(), std::find(this->items.begin(), this->items.end(), item));
	int otherItemIndex = -1;

	if (otherItem != nullptr)
	{
		if (std::find(other->items.begin(), other->items.end(), otherItem) == other->items.end())
		{
			failTransaction();
			return;
		}

		otherItemIndex = std::distance(other->items.begin(), std::find(other->items.begin(), other->items.end(), otherItem));
	}

	// Remove items with no safety checking, no reason it should fail at this stage
	other->tryRemove(otherItem, [=](Item* otherRemovedItem)
	{
		this->tryRemove(item, [=](Item* removedItem)
		{
			other->forceInsert(removedItem, false);
			this->forceInsert(otherRemovedItem, false);

			// Move the transacted items to the correct place (best effort, but it should work)
			other->moveItem(removedItem, otherItemIndex, nullptr, nullptr, doSave);
			this->moveItem(otherRemovedItem, itemIndex, nullptr, nullptr, doSave);

			// Callback success
			onTransact(removedItem, otherRemovedItem);
		},
		[=](Item* removedItem)
		{
			// Return the first removed item to where it came from
			other->forceInsert(otherRemovedItem);

			LogUtils::logError("Error removing self item during transaction");

			if (removedItem != nullptr)
			{
				LogUtils::logError(removedItem->getName());
			}
		});
	},
	[=](Item* otherRemovedItem)
	{
		LogUtils::logError("Error removing other item during transaction");

		if (otherRemovedItem != nullptr)
		{
			LogUtils::logError(otherRemovedItem->getName());
		}
	});
}

void Inventory::moveItem(Item* item, int destinationIndex, std::function<void(Item*)> onMove, std::function<void(Item*)> onMoveFailed, bool doSave)
{
	// Check if items exists
	if (std::find(this->items.begin(), this->items.end(), item) == this->items.end())
	{
		if (onMoveFailed != nullptr)
		{
			onMoveFailed(item);
		}

		return;
	}

	// Remove item
	this->items.erase(std::remove(this->items.begin(), this->items.end(), item), this->items.end());

	// Re-insert item
	destinationIndex = MathUtils::clamp(destinationIndex, 0, this->items.size());
	this->items.insert(this->items.begin() + destinationIndex, item);

	if (doSave)
	{
		this->save();
	}

	this->rebuildLookupTable();
}

bool Inventory::canInsertItemIfUnique(Item* item)
{
	int uniqueCount = item->getUniqueCount();

	if (uniqueCount >= 1)
	{
		// Count how many duplicates exist
		for (auto next : this->items)
		{
			if (item->getItemName() == next->getItemName())
			{
				uniqueCount--;
			}
		}

		// Unique cap hit!
		if (uniqueCount <= 0)
		{
			return false;
		}
	}

	return true;
}

void Inventory::rebuildLookupTable()
{
	if (this->disableLookupTableRebuilding)
	{
		return;
	}
	
	this->itemLookup.clear();

	for (auto next : this->items)
	{
		this->itemLookup.insert(next->getItemName());
	}
}
