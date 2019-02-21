#include "Inventory.h"

#include "cocos/base/CCValue.h"

using namespace cocos2d;

const int Inventory::InfiniteCapacity = -1;

Inventory::Inventory(int capacity)
{
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

cocos2d::ValueMap Inventory::serialize()
{
	// TODO

	return cocos2d::ValueMap();
}

void Inventory::deserialize(cocos2d::ValueMap& valueMap)
{
	// TODO
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
}

void Inventory::tryInsert(Item* item, std::function<void(Item*)> onInsert, std::function<void(Item*)> onInsertFailed)
{
	if (this->capacity == Inventory::InfiniteCapacity || this->items.size() < this->capacity)
	{
		this->items.push_back(item);

		if (onInsert != nullptr)
		{
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
	}
}
