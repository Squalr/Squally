#pragma once

#include "Menus/Inventory/MenuEntry.h"
#include "Menus/Inventory/ItemMenu/ItemPreview.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class Item;

class ItemEntry : public MenuEntry
{
public:
	static ItemEntry* create(Item* associatedItem, LocalizedString* text, std::string spriteResource = "");

	void setToggleCallback(std::function<void()> onToggle);
	std::function<void()> getToggleCallback();
	Item* getAssociatedItem();
	int getStackSize();
	void setStackSize(int stackSize);
	void setCraftCount(int craftCount);
	void setEquipHintMode(ItemPreview::EquipHintMode equipHintMode);
	ItemPreview::EquipHintMode getEquipHintMode();

protected:
	ItemEntry(Item* associatedItem, LocalizedString* text, std::string spriteResource);
	virtual ~ItemEntry();

private:
	typedef MenuEntry super;

	ConstantString* stackString;
	ConstantString* craftString;
	Item* associatedItem;
	int craftCount;
	int stackSize;
	ItemPreview::EquipHintMode equipHintMode;
	
	std::function<void()> onToggle;
};
