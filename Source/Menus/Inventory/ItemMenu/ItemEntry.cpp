#include "ItemEntry.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Menus/Inventory/MenuEntry.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

using namespace cocos2d;

ItemEntry* ItemEntry::create(Item* associatedItem, LocalizedString* text, std::string spriteResource)
{
    ItemEntry* instance = new ItemEntry(associatedItem, text, spriteResource);

    instance->autorelease();

    return instance;
}

ItemEntry::ItemEntry(Item* associatedItem, LocalizedString* text, std::string spriteResource) : super(text, spriteResource)
{
    this->associatedItem = associatedItem;
    this->onToggle = nullptr;
    this->hideIcon();
}

ItemEntry::~ItemEntry()
{
}

void ItemEntry::setToggleCallback(std::function<void()> onToggle)
{
    this->onToggle = onToggle;
}

std::function<void()> ItemEntry::getToggleCallback()
{
    return this->onToggle;
}

Item* ItemEntry::getAssociatedItem()
{
    return this->associatedItem;
}
