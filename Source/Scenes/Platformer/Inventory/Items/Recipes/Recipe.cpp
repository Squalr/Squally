#include "Recipe.h"

using namespace cocos2d;

Recipe::Recipe(CurrencyInventory* cost) : super(cost, ItemMeta(1, 1))
{
    this->reagentsNode = Node::create();
    this->reagentsCache = std::vector<std::tuple<Item*, int>>();

    this->craftedItems = std::vector<Item*>();
    this->reagentsNode->setVisible(false);

    this->addChild(this->reagentsNode);
}

Recipe::~Recipe()
{
}

std::vector<std::tuple<Item*, int>> Recipe::getReagents()
{
    if (this->reagentsCache.empty())
    {
        this->reagentsCache = this->getReagentsInternal();

        for (auto reagent : this->reagentsCache)
        {
            this->reagentsNode->addChild(std::get<0>(reagent));
        }
    }

    return this->reagentsCache;
}
	
std::vector<Item*>& Recipe::getCraftedItemsRef()
{
    if (this->craftedItems.empty())
    {
        this->craftedItems = this->craft();

        for (Item* item : craftedItems)
        {
            this->addChild(item);
        }
    }

    return this->craftedItems;
}
