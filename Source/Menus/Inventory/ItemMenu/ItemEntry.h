#pragma once

#include "Menus/Inventory/MenuEntry.h"
#include "Menus/Inventory/ItemMenu/ItemPreview.h"

class ConstantString;
class Item;

class ItemEntry : public MenuEntry
{
public:
	static ItemEntry* create(Item* associatedItem, LocalizedString* text, std::string spriteResource = "");

	void setToggleCallback(std::function<void()> onToggle);
	std::function<void()> getToggleCallback();
	Item* getAssociatedItem();
	void setText(LocalizedString* newText);
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

	LocalizedString* textString = nullptr;
	ConstantString* stackString = nullptr;
	ConstantString* craftString = nullptr;
	Item* associatedItem = nullptr;
	int craftCount = 0;
	int stackSize = 1;
	ItemPreview::EquipHintMode equipHintMode = ItemPreview::EquipHintMode::None;
	
	std::function<void()> onToggle = nullptr;
};
