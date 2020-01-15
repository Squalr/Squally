#include "CraftFilterMenu.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/MathUtils.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/AllWeaponsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/AxesFilter.h"
#include "Menus/Crafting/CraftFilterMenu/BowsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/MacesFilter.h"
#include "Menus/Crafting/CraftFilterMenu/SpearsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/SwordsFilter.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float CraftFilterMenu::LabelSpacing = 96.0f;

CraftFilterMenu* CraftFilterMenu::create(std::function<void()> onFilterChange)
{
	CraftFilterMenu* itemPreview = new CraftFilterMenu(onFilterChange);

	itemPreview->autorelease();

	return itemPreview;
}

CraftFilterMenu::CraftFilterMenu(std::function<void()> onFilterChange)
{
	this->isFocused = true;
	this->filterSelectionIndex = 0;
	this->onFilterChange = onFilterChange;
	this->filterNodeContent = Node::create();
	this->filterNode = SmartClippingNode::create(this->filterNodeContent, Rect(Vec2(-160.0f, -304.0f), Size(320.0f, 608.0f)));
	this->filterSelectionArrow = Sprite::create(UIResources::Menus_InventoryMenu_Arrow);
	this->selectedFilterRowActive = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectActive);
	this->selectedFilterRowInactive = Sprite::create(UIResources::Menus_InventoryMenu_RowSelectInactive);

	this->filters.push_back(AllWeaponsFilter::create());
	this->filters.push_back(AxesFilter::create());
	this->filters.push_back(BowsFilter::create());
	this->filters.push_back(MacesFilter::create());
	this->filters.push_back(SpearsFilter::create());
	this->filters.push_back(SwordsFilter::create());

	for (auto it = this->filters.begin(); it != this->filters.end(); it++)
	{
		this->filterNodeContent->addChild(*it);
	}

	this->addChild(this->selectedFilterRowActive);
	this->addChild(this->selectedFilterRowInactive);
	this->addChild(this->filterNode);
	this->addChild(this->filterSelectionArrow);
}

CraftFilterMenu::~CraftFilterMenu()
{
}

void CraftFilterMenu::onEnter()
{
	super::onEnter();

	this->focus();
	this->positionFilterText();
}

void CraftFilterMenu::initializePositions()
{
	super::initializePositions();

	this->filterSelectionArrow->setPosition(Vec2(-188.0f, 0.0f));
}

void CraftFilterMenu::initializeListeners()
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

void CraftFilterMenu::focus()
{
	this->isFocused = true;
	this->filterSelectionArrow->setVisible(true);
	this->selectedFilterRowActive->setVisible(true);
	this->selectedFilterRowInactive->setVisible(false);
}

void CraftFilterMenu::unfocus()
{
	this->isFocused = false;
	this->filterSelectionArrow->setVisible(false);
	this->selectedFilterRowActive->setVisible(false);
	this->selectedFilterRowInactive->setVisible(true);
}

CraftFilterEntry* CraftFilterMenu::getActiveFilter()
{
	return this->filters[this->filterSelectionIndex];
}

void CraftFilterMenu::scrollFilterUp()
{
	if (!this->isFocused)
	{
		return;
	}

	int previousIndex = this->filterSelectionIndex;
	this->filterSelectionIndex = MathUtils::clamp(this->filterSelectionIndex - 1, 0, this->filters.size() - 1);
	this->positionFilterText();

	if (previousIndex != this->filterSelectionIndex && this->onFilterChange != nullptr)
	{
		this->onFilterChange();
	}
}

void CraftFilterMenu::scrollFilterDown()
{
	if (!this->isFocused)
	{
		return;
	}

	int previousIndex = this->filterSelectionIndex;
	this->filterSelectionIndex = MathUtils::clamp(this->filterSelectionIndex + 1, 0, this->filters.size() - 1);
	this->positionFilterText();

	if (previousIndex != this->filterSelectionIndex && this->onFilterChange != nullptr)
	{
		this->onFilterChange();
	}
}

void CraftFilterMenu::positionFilterText()
{
	int adjustedIndex = this->filterSelectionIndex - this->filters.size() / 2;
	float offset = float(adjustedIndex) * CraftFilterMenu::LabelSpacing;

	this->filterNodeContent->setPositionY(offset);

	const float offsetY = CraftFilterMenu::LabelSpacing * float(this->filters.size() / 2);
	int index = 0;

	for (auto it = this->filters.begin(); it != this->filters.end(); it++, index++)
	{
		(*it)->setPositionX(0.0f);
		(*it)->setPositionY(float(index) * -CraftFilterMenu::LabelSpacing + offsetY);
		(*it)->setPositionZ(0.0f);
	}

	const float XOffset = 64.0f;
	const float YOffset = 6.0f;
	const float ZOffset = 128.0f;
	
	this->filters[this->filterSelectionIndex]->setPositionX(XOffset);
	this->filters[this->filterSelectionIndex]->setPositionY(this->filters[this->filterSelectionIndex]->getPositionY() + YOffset);
	this->filters[this->filterSelectionIndex]->setPositionZ(ZOffset);
}
