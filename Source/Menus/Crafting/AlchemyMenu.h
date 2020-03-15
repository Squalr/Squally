#pragma once
#include <functional>

#include "Menus/Crafting/CraftingMenuBase.h"

namespace cocos2d
{
	class Sprite;
};

class AlchemyMenu : public CraftingMenuBase
{
public:
	static AlchemyMenu* create();

protected:
	AlchemyMenu();
	virtual ~AlchemyMenu();

	void initializePositions() override;

private:
	typedef CraftingMenuBase super;

	cocos2d::Sprite* anvil;
	cocos2d::Sprite* icon;
};
