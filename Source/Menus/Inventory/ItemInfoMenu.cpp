#include "ItemInfoMenu.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemMenu/ItemPreview.h"

#include "Strings/Strings.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

ItemInfoMenu* ItemInfoMenu::create()
{
	ItemInfoMenu* instance = new ItemInfoMenu();

	instance->autorelease();

	return instance;
}

ItemInfoMenu::ItemInfoMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->itemWindow = Sprite::create(UIResources::Menus_PauseMenu_PauseMenu);
	this->itemPreview = ItemPreview::create(true, true);
	this->itemLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Inventory_Item::create());
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->returnClickCallback = nullptr;
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);

	LocalizedLabel*	takeItemLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Inventory_Take::create());
	LocalizedLabel*	takeItemLabelHover = takeItemLabel->clone();

	takeItemLabel->enableOutline(Color4B::BLACK, 2);
	takeItemLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	takeItemLabel->enableGlow(Color4B::BLACK);
	takeItemLabelHover->enableOutline(Color4B::BLACK, 2);
	takeItemLabelHover->setTextColor(Color4B::YELLOW);
	takeItemLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	takeItemLabelHover->enableGlow(Color4B::ORANGE);

	this->takeItemButton = ClickableTextNode::create(
		takeItemLabel,
		takeItemLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

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

	this->itemLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->itemLabel->enableGlow(Color4B::BLACK);
	
	this->addChild(this->backdrop);
	this->addChild(this->itemWindow);
	this->addChild(this->itemPreview);
	this->addChild(this->itemLabel);
	this->addChild(this->closeButton);
	this->addChild(this->takeItemButton);
	this->addChild(this->returnButton);
}

ItemInfoMenu::~ItemInfoMenu()
{
}

void ItemInfoMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->itemWindow, delay, duration);
	GameUtils::fadeInObject(this->itemLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->takeItemButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
}

void ItemInfoMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->itemWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->itemPreview->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 192.0f));
	this->itemLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 292.0f, visibleSize.height / 2.0f + 376.0f));
	this->takeItemButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 320.0f + 128.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 320.0f));
}

void ItemInfoMenu::initializeListeners()
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
}

void ItemInfoMenu::open(Item* item, std::function<void()> takeItemCallback)
{
	this->itemPreview->preview(ItemPreview::EquipHintMode::None, item);

	if (takeItemCallback != nullptr)
	{
		this->takeItemButton->setVisible(true);
		this->takeItemButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
		{
			takeItemCallback();
			this->close();
		});
	}
	else
	{
		this->takeItemButton->setVisible(false);
		this->takeItemButton->setMouseClickCallback(nullptr);
	}
}

void ItemInfoMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void ItemInfoMenu::close()
{
	if (this->returnClickCallback != nullptr)
	{
		this->returnClickCallback();
	}
}
