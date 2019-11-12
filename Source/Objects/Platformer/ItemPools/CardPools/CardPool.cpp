#include "CardPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CardPool::CardPool(int minCards, int maxCards) : super()
{
	this->remainingCards = RandomHelper::random_int(minCards, maxCards);
	this->equipmentInventory = EquipmentInventory::create(SaveKeys::SaveKeySquallyEquipment);
	this->inventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);

	this->addChild(equipmentInventory);
	this->addChild(inventory);
}

CardPool::~CardPool()
{
}

Item* CardPool::getCard()
{
	if (this->remainingCards-- <= 0)
	{
		return nullptr;
	}
	
	HexusCard* item = static_cast<HexusCard*>(this->getItemFromPool(true));

	if (item == nullptr)
	{
		return item;
	}

	std::map<std::string, int> cardCounts = equipmentInventory->getCardKeyCount(inventory);
	std::string cardKey = item->getCardKey();

	if (cardCounts.find(cardKey) != cardCounts.end() && cardCounts[cardKey] >= 3)
	{
		this->remainingCards++;

		// This item cannot be in the pool, as it would push the user over the 3 card limit. Sample a different card.
		return this->getCard();
	}

	return item;
} 

std::vector<Item*> CardPool::getCards()
{
	std::vector<Item*> cards = std::vector<Item*>();

	while (this->remainingCards > 0)
	{
		Item* item = this->getCard();

		if (item == nullptr)
		{
			break;
		}

		cards.push_back(item);
	}

	return cards;
}
