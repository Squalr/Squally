#include "DismantleMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterMenu.h"
#include "Menus/Crafting/CraftFilterMenu/Dismantle/AllEquipmentFilter.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"

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

DismantleMenu::DismantleMenu()
{
	this->smeltingPot = Sprite::create(UIResources::Menus_CraftingMenu_SmeltingPot);
	this->icon = Sprite::create(UIResources::Menus_CraftingMenu_SmeltingIcon);
	this->craftSound = Sound::create(SoundResources::Menus_Crafting_Blacksmithing);

	this->filterMenu->addFilter(AllEquipmentFilter::create());

	this->backDecorNode->addChild(this->smeltingPot);
	this->craftIconNode->addChild(this->icon);
	this->addChild(this->craftSound);
}

DismantleMenu::~DismantleMenu()
{
}

void DismantleMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Vec2 SmeltingPotOffset = Vec2(-72.0f, 0.0f);

	this->smeltingPot->setPosition(Vec2(visibleSize.width / 2.0f + 359.0f, visibleSize.height / 2.0f + 54.0f) + SmeltingPotOffset);
}

void DismantleMenu::open(std::vector<Item*> recipes)
{
	// There shouldn't be any recipes passed to this. Instead, we create a DismantleRecipe for every item in the players inventory.
	ObjectEvents::QueryObject<Squally>([=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			entityInventoryBehavior->getInventory();
		});
	}, Squally::MapKey);
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
}
