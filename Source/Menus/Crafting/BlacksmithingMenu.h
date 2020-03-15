#pragma once
#include <functional>

#include "Menus/Crafting/CraftingMenuBase.h"

namespace cocos2d
{
	class Sprite;
};

class BlacksmithingMenu : public CraftingMenuBase
{
public:
	static BlacksmithingMenu* create();

protected:
	BlacksmithingMenu();
	virtual ~BlacksmithingMenu();

	void initializePositions() override;
	void initializeListeners() override;

	void onCraftPreview(Item* item) override;

private:
	typedef CraftingMenuBase super;

	cocos2d::Sprite* anvil;
	ClickableNode* craftButton;
	cocos2d::Sprite* craftButtonDisabled;
};
