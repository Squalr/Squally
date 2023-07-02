#include "QuickSwapMenu.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

QuickSwapMenu* QuickSwapMenu::create()
{
	QuickSwapMenu* instance = new QuickSwapMenu();

	instance->autorelease();

	return instance;
}

QuickSwapMenu::QuickSwapMenu()
{
	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 192), visibleSize.width, visibleSize.height);
	this->window = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_PauseMenu_CloseButton, UIResources::Menus_PauseMenu_CloseButtonSelected);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Party_Party::create());

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelSelected = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelSelected->enableOutline(Color4B::BLACK, 2);
	returnLabelSelected->setTextColor(Color4B::YELLOW);
	returnLabelSelected->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	returnLabelSelected->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->titleLabel->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	this->titleLabel->enableGlow(Color4B::BLACK);

	this->addChild(this->backdrop);
	this->addChild(this->window);
	this->addChild(this->titleLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

QuickSwapMenu::~QuickSwapMenu()
{
}

void QuickSwapMenu::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->window->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void QuickSwapMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onReturnClick();
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->onReturnClick();
	});
	
	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);
}

void QuickSwapMenu::open()
{
	this->returnButton->setVisible(true);
}

void QuickSwapMenu::onReturnClick()
{
	this->stopAllActions();
	
	if (this->returnClickCallback != nullptr && this->returnButton->isVisible())
	{
		this->returnClickCallback();
	}
}

void QuickSwapMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}
