#include "ItemChance.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ItemChance* ItemChance::create(Item* item, Probability probability)
{
    ItemChance* instance = new ItemChance(item, probability);

    instance->autorelease();

    return instance;
}

ItemChance::ItemChance(Item* item, Probability probability) : super()
{
    this->item = item;
    this->probability = probability;

    if (this->item != nullptr)
    {
        this->addChild(this->item);
    }
}

ItemChance::~ItemChance()
{
}

Item* ItemChance::getItem()
{
    return this->item;
}

float ItemChance::calculateProbability(std::vector<Inventory*> inventories)
{
    int uniqueCount = this->item == nullptr ? -1 : this->item->getUniqueCount();
    int rubberBand = this->item == nullptr ? -1 : this->item->getRubberBand();
    float rubberBandFactor = this->item == nullptr ? 0.0f : this->item->getRubberBandFactor();
    int currentCount = 0;
    float chance = 0.0f;

    // Return 0% if the item has hit its unique cap
    if (this->item != nullptr && uniqueCount > 0)
    {
        for (auto it = inventories.begin(); it != inventories.end(); it++)
        {
            for (auto nextItem : (*it)->getItems())
            {
                if (nextItem != nullptr && nextItem->getItemName() == this->item->getItemName())
                {
                    currentCount++;

                    if (currentCount >= uniqueCount)
                    {
                        return 0.0f;
                    }
                }
            }
        }
    }

    switch(this->probability)
    {
        default:
        case Probability::Guaranteed:
        {
            // 100%
            chance = 1.0f;
            break;
        }
        case Probability::VeryCommon:
        {
            // 75%
            chance = 0.75f;
            break;
        }
        case Probability::Common:
        {
            // 40%
            chance = 0.40f;
            break;
        }
        case Probability::Uncommon:
        {
            // 15%
            chance = 0.15f;
            break;
        }
        case Probability::Rare:
        {
            // 8%
            chance = 0.08f;
            break;
        }
        case Probability::Epic:
        {
            // 2%
            chance = 0.02f;
            break;
        }
        case Probability::Legendary:
        {
            // 1%
            chance = 0.01f;
            break;
        }
    }

    // If rubber banding enabled, offset the probability based on the current delta from the rubber band value.
    // For example: Rubberbanding the player to only have 3 health potions, with a factor of 0.05f, and a base probability of 15%:
    // If they currently have 0 potions: rubberBand - currentCount = 3 => 15% + (3 * 0.05f) => 30%
    // If they currently have 1 potions: rubberBand - currentCount = 2 => 15% + (2 * 0.05f) => 25%
    // If they currently have 2 potions: rubberBand - currentCount = 1 => 15% + (1 * 0.05f) => 20%
    // If they currently have 3 potions: (no changes, 15%)
    // If they currently have 4 potions: rubberBand - currentCount = -1 => 15% + (-1 * 0.05f) => 10%
    // If they currently have 5 potions: rubberBand - currentCount = -2 => 15% + (-2 * 0.05f) => 5%
    // If they currently have 6 potions: rubberBand - currentCount = -3 => 15% + (-3 * 0.05f) => MIN_CAP
    if (this->probability != Probability::Guaranteed && rubberBand >= 0)
    {
        const float MinRubberBand = chance / 10.0f;

        chance += rubberBandFactor * float(rubberBand - currentCount);

        chance = MathUtils::clamp(chance, MinRubberBand, 1.0f);
    }

    return MathUtils::clamp(chance, 0.0f, 1.0f);
}
