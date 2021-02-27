#pragma once
#include <functional>

#include "Menus/Crafting/CraftingMenuBase.h"

namespace cocos2d
{
	class Sprite;
};

class Sound;

class DismantleMenu : public CraftingMenuBase
{
public:
	static DismantleMenu* create();

protected:
	DismantleMenu();
	virtual ~DismantleMenu();

	void initializePositions() override;
	void onCraftStart() override;
	void onCraftEnd(bool viaCancel) override;

private:
	typedef CraftingMenuBase super;

	cocos2d::Sprite* anvil;
	cocos2d::Sprite* icon;
	Sound* craftSound;
};
