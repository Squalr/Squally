#include "SaveSelectMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/MenuBackground.h"
#include "Scenes/Cutscenes/IntroCutscene/IntroCutscene.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Menus/ContinueGame.h"
#include "Strings/Menus/NewGame.h"

using namespace cocos2d;

SaveSelectMenu* SaveSelectMenu::instance;

void SaveSelectMenu::registerGlobalScene()
{
	if (SaveSelectMenu::instance == nullptr)
	{
		SaveSelectMenu::instance = new SaveSelectMenu();

		SaveSelectMenu::instance->autorelease();
		SaveSelectMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(SaveSelectMenu::instance);
}

SaveSelectMenu::SaveSelectMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Size shadowSize = Size(-2.0f, -2.0f);
	const int shadowBlur = 2;
	const int hoverOutlineSize = 2;
	const Color3B textColor = Color3B::WHITE;
	const Color4B shadowColor = Color4B::BLACK;
	const Color3B highlightColor = Color3B::YELLOW;
	const Color4B glowColor = Color4B::ORANGE;
	const Vec2 labelOffset = Vec2(48.0f, 0.0f);

	this->setFadeSpeed(0.0f);

	this->backgroundNode = Node::create();

	LocalizedLabel*	backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel*	backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);


	LocalizedLabel*	saveGame1Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_ContinueGame::create());
	LocalizedLabel*	saveGame1LabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_ContinueGame::create());

	saveGame1Label->setColor(textColor);
	saveGame1Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame1Label->enableGlow(shadowColor);

	saveGame1LabelHover->setColor(highlightColor);
	saveGame1LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame1LabelHover->enableGlow(glowColor);

	this->saveGame1 = ClickableTextNode::create(
		saveGame1Label,
		saveGame1LabelHover,
		UIResources::Menus_MinigamesMenu_Banner,
		UIResources::Menus_MinigamesMenu_BannerHover);

	this->saveGame1->setTextOffset(labelOffset);

	Sprite* saveGame1Icon = Sprite::create(UIResources::Menus_Icons_BookSpellsArcane);

	saveGame1Icon->setAnchorPoint(Vec2(0.0f, 0.5f));
	saveGame1Icon->setPosition(Vec2(-this->saveGame1->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->saveGame1->addChild(saveGame1Icon);

	LocalizedLabel*	saveGame2Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_NewGame::create());
	LocalizedLabel*	saveGame2LabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_NewGame::create());
	
	saveGame2Label->setColor(textColor);
	saveGame2Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame2Label->enableGlow(shadowColor);

	saveGame2LabelHover->setColor(highlightColor);
	saveGame2LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame2LabelHover->enableGlow(glowColor);

	this->saveGame2 = ClickableTextNode::create(
		saveGame2Label,
		saveGame2LabelHover,
		UIResources::Menus_MinigamesMenu_Banner,
		UIResources::Menus_MinigamesMenu_BannerHover);

	this->saveGame2->setTextOffset(labelOffset);

	Sprite* saveGame2Icon = Sprite::create(UIResources::Menus_Icons_Health);

	saveGame2Icon->setAnchorPoint(Vec2(0.0f, 0.5f));
	saveGame2Icon->setPosition(Vec2(-this->saveGame2->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->saveGame2->addChild(saveGame2Icon);

	LocalizedLabel*	saveGame3Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_NewGame::create());
	LocalizedLabel*	saveGame3LabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_NewGame::create());

	saveGame3Label->setColor(textColor);
	saveGame3Label->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame3Label->enableGlow(shadowColor);

	saveGame3LabelHover->setColor(highlightColor);
	saveGame3LabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGame3LabelHover->enableGlow(glowColor);

	this->saveGame3 = ClickableTextNode::create(
		saveGame3Label,
		saveGame3LabelHover,
		UIResources::Menus_MinigamesMenu_Banner,
		UIResources::Menus_MinigamesMenu_BannerHover);

	this->saveGame3->setTextOffset(labelOffset);

	Sprite* saveGame3Icon = Sprite::create(UIResources::Menus_Icons_Health);

	saveGame3Icon->setAnchorPoint(Vec2(0.0f, 0.5f));
	saveGame3Icon->setPosition(Vec2(-this->saveGame3->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->saveGame3->addChild(saveGame3Icon);

	this->addChild(this->backgroundNode);
	this->addChild(this->saveGame1);
	this->addChild(this->saveGame2);
	this->addChild(this->saveGame3);
	this->addChild(this->backButton);
}

SaveSelectMenu::~SaveSelectMenu()
{
}

void SaveSelectMenu::onEnter()
{
	super::onEnter();

	this->backgroundNode->addChild(MenuBackground::claimInstance());

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->saveGame1, delay, duration);
	GameUtils::fadeInObject(this->saveGame2, delay, duration);
	GameUtils::fadeInObject(this->saveGame3, delay, duration);
	GameUtils::fadeInObject(this->backButton, delay, duration);

	this->scheduleUpdate();
}

void SaveSelectMenu::initializeListeners()
{
	super::initializeListeners();

	SaveSelectMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateSaveSelect, [](EventCustom* args)
	{
		GlobalDirector::loadScene(SaveSelectMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(SaveSelectMenu::onKeyPressed, this);
	this->saveGame1->setMouseClickCallback(CC_CALLBACK_0(SaveSelectMenu::onSaveGame1Click, this));
	this->saveGame2->setMouseClickCallback(CC_CALLBACK_0(SaveSelectMenu::onSaveGame2Click, this));
	this->saveGame3->setMouseClickCallback(CC_CALLBACK_0(SaveSelectMenu::onSaveGame3Click, this));
	this->backButton->setMouseClickCallback(CC_CALLBACK_0(SaveSelectMenu::onBackClick, this));

	this->addEventListener(keyboardListener);
}

void SaveSelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->saveGame1->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 192.0f));
	this->saveGame2->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 0.0f));
	this->saveGame3->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 192.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void SaveSelectMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}
	
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void SaveSelectMenu::onSaveGame1Click()
{
	NavigationEvents::navigateWorldMap();
}

void SaveSelectMenu::onSaveGame2Click()
{
	NavigationEvents::navigateCutscene(NavigationEvents::NavigateCutsceneArgs(IntroCutscene::create([=]() { NavigationEvents::navigateWorldMap(); })));
}

void SaveSelectMenu::onSaveGame3Click()
{
	NavigationEvents::navigateCutscene(NavigationEvents::NavigateCutsceneArgs(IntroCutscene::create([=]() { NavigationEvents::navigateWorldMap(); })));
}

void SaveSelectMenu::onBackClick()
{
	NavigationEvents::navigateBack();
}
