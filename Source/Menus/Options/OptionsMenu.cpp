#include "OptionsMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Options/GeneralTab.h"
#include "Menus/Options/LanguageTab.h"
#include "Menus/Options/MemesTab.h"
#include "Menus/Options/VideoTab.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Options/GeneralOptions.h"
#include "Strings/Menus/Options/Language.h"
#include "Strings/Menus/Options/Memes.h"
#include "Strings/Menus/Options/VideoOptions.h"
#include "Strings/Menus/Options/Options.h"
#include "Strings/Menus/Return.h"
#include "Strings/Menus/Cancel.h"

using namespace cocos2d;

const Color3B OptionsMenu::TitleColor = Color3B(88, 188, 193);

OptionsMenu* OptionsMenu::create()
{
	OptionsMenu* instance = new OptionsMenu();

	instance->autorelease();

	return instance;
}

OptionsMenu::OptionsMenu()
{
	this->backClickCallback = nullptr;

	this->background = Node::create();
	this->optionsWindow = Sprite::create(UIResources::Menus_OptionsMenu_OptionsMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton2, UIResources::Menus_Buttons_CloseButton2Select);
	this->leftPanel = Node::create();
	this->rightPanel = Node::create();
	this->generalTab = GeneralTab::create();
	this->videoTab = VideoTab::create();
	this->languageTab = LanguageTab::create();
	this->memesTab = MemesTab::create();
	this->optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Options_Options::create());
	this->generalTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconLightbulb, Strings::Menus_Options_GeneralOptions::create());
	this->videoTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconCogs, Strings::Menus_Options_VideoOptions::create());
	this->languageTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconChatBubble, Strings::Menus_Options_Language::create());
	this->memesTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconWeapons, Strings::Menus_Options_Memes::create());

	this->optionsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	LocalizedLabel*	cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Cancel::create());
	LocalizedLabel*	cancelLabelHover = cancelLabel->clone();

	cancelLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabel->enableGlow(Color4B::BLACK);

	cancelLabelHover->setColor(Color3B::YELLOW);
	cancelLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabelHover->enableGlow(Color4B::ORANGE);

	this->cancelButton = ClickableTextNode::create(
		cancelLabel,
		cancelLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);

	returnLabelHover->setColor(Color3B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->leftPanel->addChild(this->generalTabButton);
	this->leftPanel->addChild(this->videoTabButton);
	this->leftPanel->addChild(this->languageTabButton);
	this->leftPanel->addChild(this->memesTabButton);
	this->rightPanel->addChild(this->generalTab);
	this->rightPanel->addChild(this->videoTab);
	this->rightPanel->addChild(this->languageTab);
	this->rightPanel->addChild(this->memesTab);
	this->addChild(this->background);
	this->addChild(this->optionsWindow);
	this->addChild(this->leftPanel);
	this->addChild(this->rightPanel);
	this->addChild(this->optionsLabel);
	this->addChild(this->closeButton);
	this->addChild(this->cancelButton);
	this->addChild(this->returnButton);
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->optionsWindow, delay, duration);
	GameUtils::fadeInObject(this->optionsLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->cancelButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
	GameUtils::fadeInObject(this->leftPanel, delay, duration);
	GameUtils::fadeInObject(this->rightPanel, delay, duration);

	this->setActiveTab(Tab::General);
}

void OptionsMenu::initializeListeners()
{
	super::initializeListeners();

	this->cancelButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onMenuCancel();  });
	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onMenuExit();  });
	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onMenuExit();  });
	this->generalTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::General); });
	this->videoTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::Video); });
	this->languageTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::Language); });
	this->memesTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::Memes); });

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handled = true;

		this->onMenuExit();
	});
}

void OptionsMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->optionsWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->optionsLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 372.0f));
	this->leftPanel->setPosition(Vec2(visibleSize.width / 2.0f - 376.0f, visibleSize.height / 2.0f + 278.0f));
	this->rightPanel->setPosition(Vec2(visibleSize.width / 2.0f + 160.0f, visibleSize.height / 2.0f + 52.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 510.0f, visibleSize.height / 2.0f + 364.0f));

	const float spacing = -66.0f;

	this->generalTabButton->setPosition(Vec2(0.0f, spacing * 0.0f));
	this->videoTabButton->setPosition(Vec2(0.0f, spacing * 1.0f));
	this->languageTabButton->setPosition(Vec2(0.0f, spacing * 2.0f));
	this->memesTabButton->setPosition(Vec2(0.0f, spacing * 3.0f));

	const float offsetY = 48.0f;

	this->cancelButton->setPosition(Vec2(visibleSize.width / 2.0f - 80.0f, visibleSize.height / 2.0f - 348.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f + 356.0f, visibleSize.height / 2.0f - 348.0f));
}

void OptionsMenu::setBackClickCallback(std::function<void()> backClickCallback)
{
	this->backClickCallback = backClickCallback;
}

void OptionsMenu::setActiveTab(Tab tab)
{
	this->activeTab = tab;

	this->generalTab->setVisible(false);
	this->videoTab->setVisible(false);
	this->languageTab->setVisible(false);
	this->memesTab->setVisible(false);

	switch(this->activeTab)
	{
		default:
		case Tab::General:
		{
			this->generalTab->setVisible(true);
			break;
		}
		case Tab::Video:
		{
			this->videoTab->setVisible(true);
			break;
		}
		case Tab::Language:
		{
			this->languageTab->setVisible(true);
			break;
		}
		case Tab::Memes:
		{
			this->memesTab->setVisible(true);
			break;
		}
	}
}

void OptionsMenu::onMenuCancel()
{
	if (this->backClickCallback != nullptr)
	{
		this->backClickCallback();
	}
}

void OptionsMenu::onMenuExit()
{
	ConfigManager::save();

	if (this->backClickCallback != nullptr)
	{
		this->backClickCallback();
	}
}

ClickableTextNode* OptionsMenu::buildTabButton(std::string iconResource, LocalizedString* localizedString)
{
	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, localizedString);
	LocalizedLabel*	labelHover = label->clone();

	ClickableTextNode* button = ClickableTextNode::create(label, labelHover, UIResources::Menus_OptionsMenu_TabButton, UIResources::Menus_OptionsMenu_TabButtonSelected);
	button->setTextOffset(Vec2(32.0f, 0.0f));

	Sprite* icon = Sprite::create(iconResource);
	icon->setPosition(Vec2(-122.0f, 0.0f));

	button->addChild(icon);

	return button;
}
