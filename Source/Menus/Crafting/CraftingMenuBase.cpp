#include "CraftingMenuBase.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterMenu.h"
#include "Menus/Crafting/CraftingPreview.h"
#include "Menus/Inventory/ItemMenu/ItemEntry.h"
#include "Menus/Inventory/ItemMenu/ItemMenu.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float CraftingMenuBase::CraftDuration = 1.5f;

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
	this->craftButton = ClickableNode::create(UIResources::Menus_CraftingMenu_CraftButton, UIResources::Menus_CraftingMenu_CraftButtonSelected);
	this->craftButtonDisabled = Sprite::create(UIResources::Menus_CraftingMenu_CraftButton);
	this->craftIconNode = Node::create();
	this->cancelIcon = Sprite::create(UIResources::Menus_CraftingMenu_CancelIcon);
	this->craftProgress = ProgressBar::create(Sprite::create(UIResources::Menus_CraftingMenu_CraftFrame), Sprite::create(UIResources::Menus_CraftingMenu_CraftBarFill));
	this->craftingLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Crafting_Crafting::create());
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->errorSound = Sound::create(SoundResources::Menus_Error1);
	this->backDecorNode = Node::create();
	this->returnClickCallback = nullptr;
	this->isCrafting = 0.0f;
	this->selectedRecipe = nullptr;

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
	this->addChild(this->craftButton);
	this->addChild(this->craftButtonDisabled);
	this->addChild(this->craftIconNode);
	this->addChild(this->cancelIcon);
	this->addChild(this->craftProgress);
	this->addChild(this->filterMenu);
	this->addChild(this->itemMenu);
	this->addChild(this->craftingLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
	this->addChild(this->errorSound);
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

	this->cancelIcon->setVisible(false);
	this->craftProgress->setVisible(false);
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->inventory = entityInventoryBehavior->getInventory();
			this->currencyInventory = entityInventoryBehavior->getCurrencyInventory();
		});
	}, Squally::MapKey);

	this->scheduleUpdate();
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
	this->craftButton->setPosition(Vec2(visibleSize.width / 2.0f + 456.0f, visibleSize.height / 2.0f - 288.0f));
	this->craftButtonDisabled->setPosition(this->craftButton->getPosition());
	this->craftIconNode->setPosition(this->craftButton->getPosition());
	this->cancelIcon->setPosition(this->craftButton->getPosition());
	this->craftProgress->setPosition(Vec2(visibleSize.width / 2.0f + 288.0f, visibleSize.height / 2.0f - 288.0f));
	this->craftingWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->craftingLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CraftingMenuBase::initializeListeners()
{
	super::initializeListeners();

	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);

	this->itemMenu->setPreviewCallback([=](Item* item)
	{
		this->onCraftPreview(item);
	});

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});

	this->craftButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->onCraftInteract();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (this->itemMenu->hasFocus())
		{
			this->onCraftInteract();
		}
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (this->isCrafting)
		{
			this->stopCraft(true);
			return;
		}

		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();
		this->close();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_D, InputEvents::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->filterMenu->unfocus();
		this->itemMenu->focus();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_A, InputEvents::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->filterMenu->focus();
		this->itemMenu->unfocus();
		this->craftingPreview->clearPreview();

		if (this->isCrafting)
		{
			this->stopCraft(true);
		}
	});
}

void CraftingMenuBase::update(float dt)
{
	super::update(dt);

	if (!this->isCrafting)
	{
		return;
	}

	this->craftElapsedTime += dt;

	this->craftProgress->setProgress(this->craftElapsedTime / CraftingMenuBase::CraftDuration);

	if (this->craftElapsedTime >= CraftingMenuBase::CraftDuration)
	{
		this->craftItem();
		this->stopCraft(false);
	}
}

void CraftingMenuBase::onFilterChange()
{
	this->itemMenu->clearPreview();
	this->craftingPreview->clearPreview();
	this->populateItemList();
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
		entry->setCraftCount(this->getCraftCount(dynamic_cast<Recipe*>(item), this->inventory));
	}

	this->itemMenu->updateAndPositionItemText();
}

void CraftingMenuBase::open(std::vector<Item*> recipes)
{
	this->recipes = recipes;
	this->onCraftPreview(this->selectedRecipe);
	this->onFilterChange();
}

void CraftingMenuBase::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

int CraftingMenuBase::getCraftCount(Recipe* recipe, Inventory* inventory)
{
	if (recipe == nullptr || this->inventory == nullptr)
	{
		return 0;
	}

	std::vector<std::tuple<Item*, int>> reagents = recipe->getReagents();

	int craftCount = 1000;

	for (auto reagent : reagents)
	{
		Item* next = std::get<0>(reagent);
		int requiredCount = std::get<1>(reagent);
		int existingCount = 0;

		for (auto item : this->inventory->getItems())
		{
			if (item->getItemName() == next->getItemName())
			{
				existingCount++;
			}
		}

		int reagentCraftAmount = requiredCount == 0 ? requiredCount : (existingCount / requiredCount);

		craftCount = std::min(craftCount, reagentCraftAmount);
	}

	return craftCount;
}

void CraftingMenuBase::onCraftPreview(Item* item)
{
	this->canCraft = this->craftingPreview->preview(dynamic_cast<Recipe*>(item), this->inventory);
	
	if (this->canCraft)
	{
		this->craftButton->enableInteraction();
		this->craftButton->setVisible(true);
		this->craftButtonDisabled->setVisible(false);
	}
	else
	{
		this->craftButton->disableInteraction();
		this->craftButton->setVisible(false);
		this->craftButtonDisabled->setVisible(true);
	}
}

void CraftingMenuBase::onCraftInteract()
{
	if (!this->canCraft)
	{
		this->errorSound->play();
		return;
	}
	
	if (!this->isCrafting)
	{
		this->startCraft();
	}
	else
	{
		this->stopCraft(true);
	}
}

void CraftingMenuBase::startCraft()
{
	if (!this->canCraft || this->isCrafting)
	{
		return;
	}

	this->isCrafting = true;
	this->craftElapsedTime = 0.0f;
	this->cancelIcon->setVisible(true);
	this->craftIconNode->setVisible(false);
	this->craftProgress->setVisible(true);

	this->onCraftStart();
}

void CraftingMenuBase::craftItem()
{
	Recipe* recipe = this->craftingPreview->getCurrentRecipe();

	if (recipe == nullptr)
	{
		return;
	}

	std::vector<Item*> craftedItems = recipe->craft();
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

	PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs(craftedItems, Strings::Platformer_Notifications_ItemCrafted::create()));

	this->populateItemList();
	this->craftingPreview->refresh();
}

void CraftingMenuBase::stopCraft(bool viaCancel)
{
	this->isCrafting = false;

	this->cancelIcon->setVisible(false);
	this->craftIconNode->setVisible(true);
	this->craftProgress->setVisible(false);

	this->onCraftEnd(viaCancel);
}

void CraftingMenuBase::close()
{
	this->stopCraft(true);

	if (this->returnClickCallback != nullptr)
	{
		this->returnClickCallback();
	}
}
