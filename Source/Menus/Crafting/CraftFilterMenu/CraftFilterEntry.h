#pragma once

#include "Menus/Inventory/MenuEntry.h"

namespace cocos2d
{
	class Sprite;
}

class Item;
class LocalizedLabel;
class LocalizedString;

class CraftFilterEntry : public MenuEntry
{
public:
	virtual std::vector<Item*> filter(std::vector<Item*> itemList) = 0;

protected:
	CraftFilterEntry(LocalizedString* text, std::string spriteResource);
	virtual ~CraftFilterEntry();

private:
	typedef MenuEntry super;
};
