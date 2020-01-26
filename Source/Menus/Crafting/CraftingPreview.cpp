#include "CraftingPreview.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CraftingPreview* CraftingPreview::create()
{
	CraftingPreview* itemPreview = new CraftingPreview();

	itemPreview->autorelease();

	return itemPreview;
}

CraftingPreview::CraftingPreview()
{
	this->recipe = nullptr;
	this->inventory = nullptr;
	this->previewNode = Node::create();

	this->preview(nullptr, nullptr);

	this->addChild(this->previewNode);
}

CraftingPreview::~CraftingPreview()
{
}

void CraftingPreview::onEnter()
{
	super::onEnter();
}

void CraftingPreview::initializePositions()
{
	super::initializePositions();
}

Recipe* CraftingPreview::getCurrentRecipe()
{
	return this->recipe;
}

bool CraftingPreview::preview(Recipe* recipe, Inventory* inventory)
{
	this->clearPreview();

	this->recipe = recipe;
	this->inventory = inventory;

	if (this->recipe == nullptr || this->inventory == nullptr)
	{
		return false;
	}

	std::map<Item*, int> reagents = this->recipe->getReagents();
	int index = 0;
	bool canCraft = true;

	for (auto reagent : reagents)
	{
		Item* next = reagent.first;
		Sprite* icon = Sprite::create(next->getIconResource());
		LocalizedString* counts = Strings::Common_XOverY::create();
		LocalizedLabel* countsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, counts);
		int existingCount = 0;

		for (auto item : this->inventory->getItems())
		{
			if (item->getItemName() == reagent.first->getItemName())
			{
				existingCount++;
			}
		}

		countsLabel->enableOutline(Color4B::BLACK, 2);
		countsLabel->setTextColor(existingCount < reagent.second ? Color4B::RED : Color4B::WHITE);
		counts->setStringReplacementVariables({ ConstantString::create(std::to_string(existingCount)), ConstantString::create(std::to_string(reagent.second)) });

		icon->setPosition(Vec2(0.0f, -64.0f * float(index)));
		countsLabel->setPosition(Vec2(48.0f, -64.0f * float(index)));
		countsLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

		this->previewNode->addChild(icon);
		this->previewNode->addChild(countsLabel);

		canCraft &= (existingCount >= reagent.second);

		index++;
	}

	return canCraft;
}

void CraftingPreview::refresh()
{
	this->preview(this->recipe, this->inventory);
}

void CraftingPreview::clearPreview()
{
	this->previewNode->removeAllChildren();
}
