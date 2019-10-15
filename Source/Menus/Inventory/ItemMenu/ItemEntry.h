#pragma once

#include "Menus/Inventory/MenuEntry.h"

namespace cocos2d
{
	class Sprite;
}

class Item;
class LocalizedLabel;
class LocalizedString;

class ItemEntry : public MenuEntry
{
public:

protected:
	ItemEntry(LocalizedString* text, std::string spriteResource);
	~ItemEntry();

private:
	typedef MenuEntry super;

	std::function<void()> onToggle();
};
