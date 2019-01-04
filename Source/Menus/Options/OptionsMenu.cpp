#include "OptionsMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Options/GeneralTab.h"
#include "Menus/Options/LanguageTab.h"
#include "Menus/Options/VideoTab.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Options/GeneralOptions.h"
#include "Strings/Menus/Options/Language.h"
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
	this->closeButton = MenuSprite::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->leftPanel = Node::create();
	this->rightPanel = Node::create();
	this->generalTab = GeneralTab::create();
	this->videoTab = VideoTab::create();
	this->languageTab = LanguageTab::create();
	this->optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Options_Options::create());

	LocalizedLabel*	generalLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Options_GeneralOptions::create());
	LocalizedLabel*	generalLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Options_GeneralOptions::create());

	this->generalTabButton = TextMenuSprite::create(generalLabel, generalLabelHover, UIResources::Menus_OptionsMenu_TabButton, UIResources::Menus_OptionsMenu_TabButtonSelected);
	this->generalTabButton->setTextOffset(Vec2(32.0f, 0.0f));

	Sprite* generalSprite = Sprite::create(UIResources::Menus_OptionsMenu_IconLightbulb);
	generalSprite->setPosition(Vec2(-122.0f, 0.0f));

	this->generalTabButton->addChild(generalSprite);

	LocalizedLabel*	videoLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Options_VideoOptions::create());
	LocalizedLabel*	videoLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Options_VideoOptions::create());

	this->videoTabButton = TextMenuSprite::create(videoLabel, videoLabelHover, UIResources::Menus_OptionsMenu_TabButton, UIResources::Menus_OptionsMenu_TabButtonSelected);
	this->videoTabButton->setTextOffset(Vec2(32.0f, 0.0f));

	Sprite* videoSprite = Sprite::create(UIResources::Menus_OptionsMenu_IconCogs);
	videoSprite->setPosition(Vec2(-122.0f, 0.0f));

	this->videoTabButton->addChild(videoSprite);

	LocalizedLabel*	languageLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Options_Language::create());
	LocalizedLabel*	languageLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Options_Language::create());

	this->languageTabButton = TextMenuSprite::create(languageLabel, languageLabelHover, UIResources::Menus_OptionsMenu_TabButton, UIResources::Menus_OptionsMenu_TabButtonSelected);
	this->languageTabButton->setTextOffset(Vec2(32.0f, 0.0f));

	Sprite* languageSprite = Sprite::create(UIResources::Menus_OptionsMenu_IconChatBubble);
	languageSprite->setPosition(Vec2(-122.0f, 0.0f));

	this->languageTabButton->addChild(languageSprite);

	this->optionsLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	LocalizedLabel*	cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Cancel::create());
	LocalizedLabel*	cancelLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Cancel::create());

	cancelLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabel->enableGlow(Color4B::BLACK);

	cancelLabelHover->setColor(Color3B::YELLOW);
	cancelLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabelHover->enableGlow(Color4B::ORANGE);

	this->cancelButton = TextMenuSprite::create(
		cancelLabel,
		cancelLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());

	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);

	returnLabelHover->setColor(Color3B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = TextMenuSprite::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->leftPanel->addChild(this->generalTabButton);
	this->leftPanel->addChild(this->videoTabButton);
	this->leftPanel->addChild(this->languageTabButton);
	this->rightPanel->addChild(this->generalTab);
	this->rightPanel->addChild(this->videoTab);
	this->rightPanel->addChild(this->languageTab);
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

	this->cancelButton->setClickCallback([=](MenuSprite*, MouseEvents::MouseEventArgs*) { this->onMenuCancel();  });
	this->returnButton->setClickCallback([=](MenuSprite*, MouseEvents::MouseEventArgs*) { this->onMenuExit();  });
	this->closeButton->setClickCallback([=](MenuSprite*, MouseEvents::MouseEventArgs*) { this->onMenuExit();  });
	this->generalTabButton->setClickCallback([=](MenuSprite*, MouseEvents::MouseEventArgs*) { this->setActiveTab(Tab::General); });
	this->videoTabButton->setClickCallback([=](MenuSprite*, MouseEvents::MouseEventArgs*) { this->setActiveTab(Tab::Video); });
	this->languageTabButton->setClickCallback([=](MenuSprite*, MouseEvents::MouseEventArgs*) { this->setActiveTab(Tab::Language); });

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(OptionsMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void OptionsMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->optionsWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->optionsLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 372.0f));
	this->leftPanel->setPosition(Vec2(visibleSize.width / 2.0f - 376.0f, visibleSize.height / 2.0f + 278.0f));
	this->rightPanel->setPosition(Vec2(visibleSize.width / 2.0f + 160.0f, visibleSize.height / 2.0f + 52.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f, visibleSize.height / 2.0f + 364.0f));

	const float spacing = -66.0f;

	this->generalTabButton->setPosition(Vec2(0.0f, spacing * 0.0f));
	this->videoTabButton->setPosition(Vec2(0.0f, spacing * 1.0f));
	this->languageTabButton->setPosition(Vec2(0.0f, spacing * 2.0f));

	const float offsetY = 48.0f;

	this->cancelButton->setPosition(Vec2(visibleSize.width / 2.0f - 80.0f, visibleSize.height / 2.0f - 348.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f + 356.0f, visibleSize.height / 2.0f - 348.0f));
}

void OptionsMenu::setBackClickCallback(std::function<void()> backClickCallback)
{
	this->backClickCallback = backClickCallback;
}

void OptionsMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
			this->onMenuExit();
			break;
		}
		default:
		{
			break;
		}
	}
}

void OptionsMenu::setActiveTab(Tab tab)
{
	this->activeTab = tab;

	this->generalTab->setVisible(false);
	this->videoTab->setVisible(false);
	this->languageTab->setVisible(false);

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
