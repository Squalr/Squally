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

	void open(const std::vector<Item*>& recipes) override;

protected:
	DismantleMenu();
	virtual ~DismantleMenu();

	void onEnter() override;
	void initializePositions() override;
	void onCraftStart() override;
	void onCraftEnd(bool viaCancel) override;
	virtual float getCraftDuration();
	LocalizedString* getCraftString() override;

private:
	typedef CraftingMenuBase super;

	cocos2d::Node* dismantledRecipiesNode = nullptr;
	std::vector<Item*> dismantleRecipes;
	cocos2d::Sprite* smeltingPot = nullptr;
	cocos2d::Sprite* icon = nullptr;
	Sound* craftSound = nullptr;

	static const float DismantleDuration;
};
