#include "Recipe.h"

using namespace cocos2d;

Recipe::Recipe(CurrencyInventory* cost) : super(cost, ItemMeta(1, 1))
{
    this->craftedItemsNode = Node::create();
    this->reagentsNode = Node::create();
    this->reagentsCache = std::vector<std::tuple<Item*, int>>();

    this->craftedItems = std::vector<Item*>();
    this->craftedItemsByCount = std::vector<std::tuple<Item*, int>>();
    this->reagentsNode->setVisible(false);

    this->addChild(this->craftedItemsNode);
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
	
const std::vector<Item*>& Recipe::getCraftedItemsRef()
{
    if (this->craftedItems.empty())
    {
        this->craftedItems = this->craft();

        for (Item* item : craftedItems)
        {
            this->craftedItemsNode->addChild(item);
        }
    }

    return this->craftedItems;
}

const std::vector<std::tuple<Item*, int>>& Recipe::getCraftedItemsByCountRef()
{
    if (this->craftedItemsByCount.empty())
    {
        std::map<std::string, std::vector<Item*>> craftedItemsById = std::map<std::string, std::vector<Item*>>();

        for (Item* item : this->getCraftedItemsRef())
        {
            craftedItemsById[item->getIdentifier()].push_back(item);
        }

        for (const auto& [id, items] : craftedItemsById)
        {
            this->craftedItemsByCount.push_back(std::make_tuple(items[0], int(items.size())));
        }
    }

    return this->craftedItemsByCount;
}
