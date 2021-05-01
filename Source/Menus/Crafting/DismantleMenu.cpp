#include "DismantleMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterMenu.h"
#include "Menus/Crafting/CraftFilterMenu/Dismantle/AllEquipmentFilter.h"
#include "Menus/Crafting/CraftingPreview.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Dismantle/DismantleRecipe.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DismantleMenu* DismantleMenu::create()
{
	DismantleMenu* instance = new DismantleMenu();

	instance->autorelease();

	return instance;
}

DismantleMenu::DismantleMenu() : super(Strings::Menus_Crafting_Dismantle::create())
{
	this->smeltingPot = Sprite::create(UIResources::Menus_CraftingMenu_SmeltingPot);
	this->icon = Sprite::create(UIResources::Menus_CraftingMenu_SmeltingIcon);
	this->craftSound = Sound::create(SoundResources::Menus_Crafting_Blacksmithing);
	this->dismantleRecipes = std::vector<Item*>();
	this->dismantledRecipiesNode = Node::create();

	this->filterMenu->addFilter(AllEquipmentFilter::create());
	this->craftingPreview->setDisplayMode(CraftingPreview::DisplayMode::ProducedItems);

	this->backDecorNode->addChild(this->smeltingPot);
	this->craftIconNode->addChild(this->icon);
	this->addChild(this->dismantledRecipiesNode);
	this->addChild(this->craftSound);
}

DismantleMenu::~DismantleMenu()
{
}

void DismantleMenu::onEnter()
{
	super::onEnter();
}

void DismantleMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Vec2 SmeltingPotOffset = Vec2(-72.0f, 0.0f);

	this->smeltingPot->setPosition(Vec2(visibleSize.width / 2.0f + 359.0f, visibleSize.height / 2.0f + 54.0f) + SmeltingPotOffset);
}

void DismantleMenu::open(const std::vector<Item*>& recipes)
{
	this->selectedRecipe = nullptr;
	this->dismantledRecipiesNode->removeAllChildren();
	this->dismantleRecipes.clear();

	ObjectEvents::QueryObject<Squally>([&](Squally* squally)
	{
		squally->getComponent<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			for (Item* item : entityInventoryBehavior->getInventory()->getItems())
			{
				if (dynamic_cast<Equipable*>(item) != nullptr && dynamic_cast<HexusCard*>(item) == nullptr)
				{
					DismantleRecipe* recipe = DismantleRecipe::create(item);
					this->dismantledRecipiesNode->addChild(recipe);
					this->dismantleRecipes.push_back(recipe);
				}
			}
		});
	}, Squally::MapKey);

	std::sort(this->dismantleRecipes.begin(), this->dismantleRecipes.end(), [](Item* a, Item* b) -> bool
	{
		return a->getIdentifier() < b->getIdentifier();
	});

	// There shouldn't be any recipes passed to this. Instead, we create a DismantleRecipe for every item in the players inventory
	super::open(this->dismantleRecipes);
}

void DismantleMenu::onCraftStart()
{
	this->craftSound->stop();
	this->craftSound->play();
}

void DismantleMenu::onCraftEnd(bool viaCancel)
{
	if (viaCancel)
	{
		this->craftSound->stop();
	}
	else
	{
		this->dismantleRecipes.erase(std::remove(this->dismantleRecipes.begin(), this->dismantleRecipes.end(), this->selectedRecipe), this->dismantleRecipes.end());

		// Refresh UI with the dismantled item removed. Go directly to base class since we do not need to rebuild the dismantle recipe list.
		super::open(this->dismantleRecipes);
	}
}

LocalizedString* DismantleMenu::getCraftString()
{
	return Strings::Platformer_Notifications_MaterialsRecovered::create();
}
