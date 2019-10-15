#include "FilterMenu.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Menus/Inventory/Filters/AllFilter.h"
#include "Menus/Inventory/Filters/ConsumablesFilter.h"
#include "Menus/Inventory/Filters/CraftingFilter.h"
#include "Menus/Inventory/Filters/EquipmentFilter.h"
#include "Menus/Inventory/Filters/MiscFilter.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

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

	this->filters.push_back(AllFilter::create());
	this->filters.push_back(ConsumablesFilter::create());
	this->filters.push_back(CraftingFilter::create());
	this->filters.push_back(EquipmentFilter::create());
	this->filters.push_back(MiscFilter::create());

	/**
	 * this->allLabel = this->buildMenuLabel(Strings::Menus_Inventory_All::create(), Sprite::create(UIResources::Menus_InventoryMenu_AllIcon));
		this->equipmentLabel = this->buildMenuLabel(Strings::Menus_Inventory_Equipment::create(), Sprite::create(UIResources::Menus_InventoryMenu_EquipmentIcon));
		this->consumablesLabel = this->buildMenuLabel(Strings::Menus_Inventory_Consumables::create(), Sprite::create(UIResources::Menus_InventoryMenu_ConsumablesIcon));
		this->craftingLabel = this->buildMenuLabel(Strings::Menus_Inventory_Crafting::create(), Sprite::create(UIResources::Menus_InventoryMenu_CraftingIcon));
		this->hexusLabel = this->buildMenuLabel(Strings::Menus_Inventory_Hexus::create(), Sprite::create(UIResources::Menus_InventoryMenu_HexusIcon));
		this->miscLabel = this->buildMenuLabel(Strings::Menus_Inventory_Misc::create(), Sprite::create(UIResources::Menus_InventoryMenu_MiscIcon));
	 */

	for (auto it = this->filters.begin(); it != this->filters.end(); it++)
	{
		this->filterNode->addChild(*it);
	}

	this->addChild(this->filterNode);
}

FilterMenu::~FilterMenu()
{
}

void FilterMenu::onEnter()
{
	super::onEnter();

	this->positionFilterText();
}

void FilterMenu::initializePositions()
{
	super::initializePositions();
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

void FilterMenu::scrollFilterUp()
{
	if (!this->isFocused)
	{
		return;
	}

	this->filterSelectionIndex++;
	this->positionFilterText();
}

void FilterMenu::scrollFilterDown()
{
	if (!this->isFocused)
	{
		return;
	}

	this->filterSelectionIndex--;
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

	//this->allLabel->setPositionX(XOffset);
	//this->allLabel->setPositionY(this->allLabel->getPositionY() + YOffset);
	//this->allLabel->setPositionZ(ZOffset);
}
