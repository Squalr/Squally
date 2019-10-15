#include "FilterMenu.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/MathUtils.h"
#include "Menus/Inventory/FilterMenu/AllFilter.h"
#include "Menus/Inventory/FilterMenu/ConsumablesFilter.h"
#include "Menus/Inventory/FilterMenu/CraftingFilter.h"
#include "Menus/Inventory/FilterMenu/EquipmentFilter.h"
#include "Menus/Inventory/FilterMenu/MiscFilter.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float FilterMenu::LabelSpacing = 96.0f;

FilterMenu* FilterMenu::create()
{
	FilterMenu* itemPreview = new FilterMenu();

	itemPreview->autorelease();

	return itemPreview;
}

FilterMenu::FilterMenu()
{
	this->isFocused = true;
	this->filterSelectionIndex = 0;
	this->filterNodeContent = Node::create();
	this->filterNode = SmartClippingNode::create(this->filterNodeContent, Rect(Vec2(-160.0f, -304.0f), Size(320.0f, 608.0f)));
	this->filterSelectionArrow = Sprite::create(UIResources::Menus_InventoryMenu_Arrow);
	this->selectedFilterRowActive = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectActive);
	this->selectedFilterRowInactive = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectInactive);

	this->filters.push_back(AllFilter::create());
	this->filters.push_back(ConsumablesFilter::create());
	this->filters.push_back(CraftingFilter::create());
	this->filters.push_back(EquipmentFilter::create());
	this->filters.push_back(MiscFilter::create());

	for (auto it = this->filters.begin(); it != this->filters.end(); it++)
	{
		this->filterNodeContent->addChild(*it);
	}

	this->addChild(this->selectedFilterRowActive);
	this->addChild(this->selectedFilterRowInactive);
	this->addChild(this->filterNode);
	this->addChild(this->filterSelectionArrow);
}

FilterMenu::~FilterMenu()
{
}

void FilterMenu::onEnter()
{
	super::onEnter();

	this->focus();
	this->positionFilterText();
}

void FilterMenu::initializePositions()
{
	super::initializePositions();

	this->filterSelectionArrow->setPosition(Vec2(-188.0f, 0.0f));
}

void FilterMenu::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->scrollFilterUp();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->scrollFilterDown();
	});
}

void FilterMenu::focus()
{
	this->isFocused = true;
	this->filterSelectionArrow->setVisible(true);
	this->selectedFilterRowActive->setVisible(true);
	this->selectedFilterRowInactive->setVisible(false);
}

void FilterMenu::unfocus()
{
	this->isFocused = false;
	this->filterSelectionArrow->setVisible(false);
	this->selectedFilterRowActive->setVisible(false);
	this->selectedFilterRowInactive->setVisible(true);
}

void FilterMenu::scrollFilterUp()
{
	if (!this->isFocused)
	{
		return;
	}

	this->filterSelectionIndex = MathUtils::clamp(this->filterSelectionIndex - 1, 0, this->filters.size() - 1);
	this->positionFilterText();
}

void FilterMenu::scrollFilterDown()
{
	if (!this->isFocused)
	{
		return;
	}

	this->filterSelectionIndex = MathUtils::clamp(this->filterSelectionIndex + 1, 0, this->filters.size() - 1);
	this->positionFilterText();
}

void FilterMenu::positionFilterText()
{
	int adjustedIndex = this->filterSelectionIndex - this->filters.size() / 2;
	float offset = float(adjustedIndex) * FilterMenu::LabelSpacing;

	this->filterNodeContent->setPositionY(offset);

	const float offsetY = FilterMenu::LabelSpacing * float(this->filters.size() / 2);
	int index = 0;

	for (auto it = this->filters.begin(); it != this->filters.end(); it++, index++)
	{
		(*it)->setPositionX(0.0f);
		(*it)->setPositionY(float(index) * -FilterMenu::LabelSpacing + offsetY);
		(*it)->setPositionZ(0.0f);
	}

	const float XOffset = 64.0f;
	const float YOffset = 6.0f;
	const float ZOffset = 128.0f;
	
	this->filters[this->filterSelectionIndex]->setPositionX(XOffset);
	this->filters[this->filterSelectionIndex]->setPositionY(this->filters[this->filterSelectionIndex]->getPositionY() + YOffset);
	this->filters[this->filterSelectionIndex]->setPositionZ(ZOffset);
}
