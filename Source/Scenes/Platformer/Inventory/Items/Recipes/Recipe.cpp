#include "Recipe.h"

using namespace cocos2d;

Recipe::Recipe(CurrencyInventory* cost, ItemMeta itemMeta) : super(cost, itemMeta)
{
    this->craftedItem = nullptr;
}

Recipe::~Recipe()
{
}
	
Item* Recipe::getCraftedItemRef()
{
    if (this->craftedItem == nullptr)
    {
        this->craftedItem = this->craft();

        this->addChild(this->craftedItem);
    }

    return this->craftedItem;
}
