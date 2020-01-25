#include "CraftingPreview.h"

#include "cocos/2d/CCSprite.h"

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
	this->previewNode = Node::create();

	this->preview(nullptr);

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

void CraftingPreview::preview(Recipe* recipe)
{
	this->clearPreview();

	if (recipe == nullptr)
	{
		return;
	}

	std::map<Item*, int> reagents = recipe->getReagents();
	int index = 0;

	for (auto reagent : reagents)
	{
		Item* next = reagent.first;
		Sprite* icon = Sprite::create(next->getIconResource());
		LocalizedString* counts = Strings::Common_XOverY::create();
		LocalizedLabel* countsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, counts);
		int existingCount = 0;

		countsLabel->enableOutline(Color4B::BLACK, 2);
		countsLabel->setTextColor(existingCount < reagent.second ? Color4B::RED : Color4B::WHITE);
		counts->setStringReplacementVariables({ ConstantString::create(std::to_string(existingCount)), ConstantString::create(std::to_string(reagent.second)) });

		icon->setPosition(Vec2(0.0f, -64.0f * float(index)));
		countsLabel->setPosition(Vec2(48.0f, -64.0f * float(index)));
		countsLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

		this->previewNode->addChild(icon);
		this->previewNode->addChild(countsLabel);

		index++;
	}
}

void CraftingPreview::clearPreview()
{
	this->previewNode->removeAllChildren();
}
