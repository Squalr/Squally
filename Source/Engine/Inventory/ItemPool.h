#pragma once

#include "Engine/Maps/GameObject.h"

class Item;
class ItemChance;

class ItemPool : public GameObject
{
public:

protected:
	ItemPool(const cocos2d::ValueMap& properties, std::string poolName = "");
	ItemPool(std::string poolName = "");
	~ItemPool();

	void initializeListeners() override;

	virtual Item* getItemFromPool(bool removeSampledItem);
	virtual std::vector<Item*> getItemsFromPool(int count, bool removeSampledItems);
	void addItemToPool(ItemChance* itemChance);
	void removeItemFromPool(ItemChance* itemChance);
	
	std::vector<ItemChance*> itemPool;

private:
	typedef GameObject super;

	cocos2d::Node* itemsNode;
	std::string poolName;
};
