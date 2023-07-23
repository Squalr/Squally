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
#include "Entities/Platformer/Helpers/BallmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
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
	this->window = Sprite::create(UIResources::Menus_PauseMenu_PauseMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_PauseMenu_CloseButton, UIResources::Menus_PauseMenu_CloseButtonSelected);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Party_SwapHelper::create());
	this->guanoNode = this->createHelperButton(Guano::MapKey,
		EntityResources::Helpers_EndianForest_Guano_Emblem,
		Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create());
	this->geckyNode = this->createHelperButton(Gecky::MapKey,
		EntityResources::Helpers_DataMines_Gecky_Emblem,
		Strings::Platformer_Entities_Names_Helpers_DataMines_Gecky::create());
	this->grimNode = this->createHelperButton(Grim::MapKey,
		EntityResources::Helpers_CastleValgrind_Grim_Emblem,
		Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Grim::create());

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
	this->addChild(this->guanoNode);
	this->addChild(this->geckyNode);
	this->addChild(this->grimNode);
	this->addChild(this->titleLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

QuickSwapMenu::~QuickSwapMenu()
{
}

void QuickSwapMenu::onEnter()
{
	super::onEnter();
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void QuickSwapMenu::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();
	const float Spacing = 192.0f;

	this->window->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->guanoNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + Spacing));
	this->geckyNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->grimNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - Spacing));
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

ClickableTextNode* QuickSwapMenu::createHelperButton(std::string helperNameStr, std::string helperEmblem, LocalizedString* helperName)
{
	LocalizedLabel*	helperLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, helperName);
	LocalizedLabel*	helperLabelSelected = helperLabel->clone();

	helperLabel->enableOutline(Color4B::BLACK, 2);
	helperLabel->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	helperLabel->enableGlow(Color4B::BLACK);
	helperLabelSelected->enableOutline(Color4B::BLACK, 2);
	helperLabelSelected->setTextColor(Color4B::YELLOW);
	helperLabelSelected->enableShadow(Color4B::BLACK, CSize(-2.0f, -2.0f), 2);
	helperLabelSelected->enableGlow(Color4B::ORANGE);

	ClickableTextNode* node = ClickableTextNode::create(
		helperLabel,
		helperLabelSelected,
		UIResources::Menus_PauseMenu_MapButton,
		UIResources::Menus_PauseMenu_MapButtonSelected);

	node->setTextOffset(Vec2(0.0f, -96.0f));
	node->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->squally->setState(StateKeys::CurrentHelper, Value(helperNameStr));
		this->onReturnClick();
	});

	node->addChild(Sprite::create(helperEmblem));

	return node;
}
