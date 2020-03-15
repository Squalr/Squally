#include "CraftingMenuBase.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterMenu.h"
#include "Menus/Crafting/CraftingPreview.h"
#include "Menus/Inventory/ItemMenu/ItemEntry.h"
#include "Menus/Inventory/ItemMenu/ItemMenu.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CraftingMenuBase::CraftingMenuBase()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);
	this->currencyInventory = nullptr;
	this->inventory = nullptr;
	this->craftingWindow = Sprite::create(UIResources::Menus_InventoryMenu_InventoryMenu);
	this->craftingPreview = CraftingPreview::create();
	this->filterMenu = CraftFilterMenu::create([=](){ this->onFilterChange(); });
	this->itemMenu = ItemMenu::create();
	this->recipes = std::vector<Item*>();
	this->craftingLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Crafting_Crafting::create());
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->backDecorNode = Node::create();
	this->returnClickCallback = nullptr;
	this->canCraft = false;

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->setTextColor(Color4B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->craftingLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->craftingLabel->enableGlow(Color4B::BLACK);
	
	this->addChild(this->backdrop);
	this->addChild(this->craftingWindow);
	this->addChild(this->backDecorNode);
	this->addChild(this->craftingPreview);
	this->addChild(this->filterMenu);
	this->addChild(this->itemMenu);
	this->addChild(this->craftingLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

CraftingMenuBase::~CraftingMenuBase()
{
}

void CraftingMenuBase::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->craftingWindow, delay, duration);
	GameUtils::fadeInObject(this->craftingLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
	
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
			this->currencyInventory = entityInventoryBehavior->getCurrencyInventory();
		});
	}, Squally::MapKeySqually);
}

void CraftingMenuBase::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Vec2 AnvilOffset = Vec2(-72.0f, 0.0f);

	this->filterMenu->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f, visibleSize.height / 2.0f - 44.0f));
	this->itemMenu->setPreviewOffset(ItemMenu::DefaultPreviewOffset + AnvilOffset);
	this->itemMenu->setPosition(Vec2(visibleSize.width / 2.0f - 1.0f, visibleSize.height / 2.0f - 44.0f));
	this->craftingPreview->setPosition(Vec2(visibleSize.width / 2.0f + 359.0f, visibleSize.height / 2.0f + 54.0f) + AnvilOffset + Vec2(128.0f, 64.0f));
	this->craftingWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->craftingLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CraftingMenuBase::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});

	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);

	this->itemMenu->setPreviewCallback([=](Item* item)
	{
		this->onCraftPreview(item);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();
		this->close();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->filterMenu->unfocus();
		this->itemMenu->focus();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->filterMenu->focus();
		this->itemMenu->unfocus();
		this->craftingPreview->clearPreview();
	});
}

void CraftingMenuBase::onFilterChange()
{
	this->populateItemList();
	this->itemMenu->clearPreview();
	this->craftingPreview->clearPreview();
}

void CraftingMenuBase::populateItemList()
{
	this->itemMenu->clearVisibleItems();
	std::vector<Item*> items = this->filterMenu->getActiveFilter()->filter(this->recipes);
	
	for (auto item : items)
	{
		ItemEntry* entry = this->itemMenu->pushVisibleItem(item, [=]()
		{
		});

		entry->hideIcon();
	}

	this->itemMenu->updateAndPositionItemText();
}

void CraftingMenuBase::open(std::vector<Item*> recipes)
{
	this->recipes = recipes;
	this->onFilterChange();

	this->filterMenu->focus();
	this->itemMenu->unfocus();
}

void CraftingMenuBase::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void CraftingMenuBase::onCraftPreview(Item* item)
{
	if (dynamic_cast<Recipe*>(item) == nullptr)
	{
		return;
	}

	this->canCraft = this->craftingPreview->preview(dynamic_cast<Recipe*>(item), this->inventory);
}

void CraftingMenuBase::tryCraftItem()
{
	Recipe* recipe = this->craftingPreview->getCurrentRecipe();

	if (recipe == nullptr)
	{
		return;
	}

	Item* craftedItem = recipe->craft();
	std::vector<std::tuple<Item*, int>> reagents = recipe->getReagents();

	for (auto reagent : reagents)
	{
		int foundCount = 0;

		for (auto item : this->inventory->getItems())
		{
			if (item->getItemName() == std::get<0>(reagent)->getItemName())
			{
				this->inventory->tryRemove(item);
				
				if (++foundCount >= std::get<1>(reagent))
				{
					break;
				}
			}
		}
	}

	PlatformerEvents::TriggerGiveItem(PlatformerEvents::GiveItemArgs(craftedItem, Strings::Platformer_Notifications_ItemCrafted::create()));

	this->populateItemList();
	this->craftingPreview->refresh();
}

void CraftingMenuBase::close()
{
	if (this->returnClickCallback != nullptr)
	{
		this->returnClickCallback();
	}
}
