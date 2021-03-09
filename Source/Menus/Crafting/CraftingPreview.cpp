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
	
	bool canCraft = true;
	int index = 0;

	// Trash O(n*m) algorithm. May need something better if this is slow on large inventories.
	for (const auto& reagent : this->recipe->getReagents())
	{
		Item* item = std::get<0>(reagent);
		int requiredCount = std::get<1>(reagent);
		int existingCount = 0;
		
		for (Item* inventoryItem : this->inventory->getItems())
		{
			if (inventoryItem->getIdentifier() == item->getIdentifier())
			{
				existingCount++;
			}
		}

		if (this->displayMode == DisplayMode::RequiredItems)
		{
			LocalizedString* counts = Strings::Common_XOverY::create();
			counts->setStringReplacementVariables({ ConstantString::create(std::to_string(existingCount)), ConstantString::create(std::to_string(requiredCount)) });
			this->buildPreview(item, counts, index++, existingCount < requiredCount);
		}

		canCraft &= (existingCount >= requiredCount);
	}

	if (this->displayMode == DisplayMode::ProducedItems)
	{
		for (const auto& next : this->recipe->getCraftedItemsByCountRef())
		{
			Item* item = std::get<0>(next);
			int count = std::get<1>(next);

			LocalizedString* counts = Strings::Common_TimesConstant::create();
			counts->setStringReplacementVariables({ ConstantString::create(std::to_string(count)) });
			this->buildPreview(item, counts, index++, true);
		}
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

void CraftingPreview::setDisplayMode(DisplayMode displayMode)
{
	this->displayMode = displayMode;
}

void CraftingPreview::buildPreview(Item* item, LocalizedString* text, int index, bool isValid)
{
	Sprite* icon = Sprite::create(item->getIconResource());
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);

	label->enableOutline(Color4B::BLACK, 2);
	label->setTextColor(isValid ? Color4B::WHITE : Color4B::RED);

	icon->setPosition(Vec2(0.0f, -64.0f * float(index)));
	label->setPosition(Vec2(48.0f, -64.0f * float(index)));
	label->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->previewNode->addChild(icon);
	this->previewNode->addChild(label);
}
