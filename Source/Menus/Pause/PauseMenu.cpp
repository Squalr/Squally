#include "PauseMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Options/Options.h"
#include "Strings/Menus/Pause.h"
#include "Strings/Menus/QuitToTitle.h"
#include "Strings/Menus/Resume.h"

using namespace cocos2d;

const Color3B PauseMenu::TitleColor = Color3B(88, 188, 193);

PauseMenu* PauseMenu::create()
{
	PauseMenu* instance = new PauseMenu();

	instance->autorelease();

	return instance;
}

PauseMenu::PauseMenu()
{
	this->pauseWindow = Sprite::create(UIResources::Menus_PauseMenu_PauseMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->pauseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Pause::create());
	this->resumeClickCallback = nullptr;
	this->optionsClickCallback = nullptr;
	this->exitClickCallback = nullptr;

	Size shadowSize = Size(-2.0f, -2.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	LocalizedLabel*	resumeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Resume::create());
	LocalizedLabel*	resumeLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Resume::create());

	LocalizedLabel*	optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Options_Options::create());
	LocalizedLabel*	optionsLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Options_Options::create());

	LocalizedLabel*	exitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_QuitToTitle::create());
	LocalizedLabel*	exitLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_QuitToTitle::create());

	resumeLabel->setColor(textColor);
	resumeLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	resumeLabel->enableGlow(shadowColor);
	optionsLabel->setColor(textColor);
	optionsLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabel->enableGlow(shadowColor);
	exitLabel->setColor(textColor);
	exitLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabel->enableGlow(shadowColor);

	resumeLabelHover->setColor(highlightColor);
	resumeLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	resumeLabelHover->enableGlow(glowColor);
	optionsLabelHover->setColor(highlightColor);
	optionsLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabelHover->enableGlow(glowColor);
	exitLabelHover->setColor(highlightColor);
	exitLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabelHover->enableGlow(glowColor);

	this->resumeButton = ClickableTextNode::create(
		resumeLabel,
		resumeLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->optionsButton = ClickableTextNode::create(
		optionsLabel,
		optionsLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->exitButton = ClickableTextNode::create(
		exitLabel,
		exitLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->pauseLabel->setColor(PauseMenu::TitleColor);
	this->pauseLabel->enableShadow(Color4B::BLACK, Size(2.0f, -2.0f), 2);
	
	this->addChild(this->pauseWindow);
	this->addChild(this->pauseLabel);
	this->addChild(this->closeButton);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->pauseWindow, delay, duration);
	GameUtils::fadeInObject(this->pauseLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->resumeButton, delay, duration);
	GameUtils::fadeInObject(this->optionsButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);
}

void PauseMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->pauseWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->pauseLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 230.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 136.0f, visibleSize.height / 2.0f + 204.0f));
	this->resumeButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 128.0f));
	this->optionsButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 0.0f));
	this->exitButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 180.0f));
}

void PauseMenu::initializeListeners()
{
	super::initializeListeners();

	this->resumeButton->setMouseClickCallback(CC_CALLBACK_0(PauseMenu::onResumeClick, this));
	this->optionsButton->setMouseClickCallback(CC_CALLBACK_0(PauseMenu::onOptionsClick, this));
	this->exitButton->setMouseClickCallback(CC_CALLBACK_0(PauseMenu::onExitClick, this));

	this->closeButton->setMouseClickCallback(CC_CALLBACK_0(PauseMenu::onCloseClick, this));
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handled = true;

		if (this->resumeClickCallback != nullptr)
		{
			this->resumeClickCallback();
		}
	});
}

void PauseMenu::setResumeCallback(std::function<void()> resumeClickCallback)
{
	this->resumeClickCallback = resumeClickCallback;
}

void PauseMenu::setOptionsCallback(std::function<void()> optionsClickCallback)
{
	this->optionsClickCallback = optionsClickCallback;
}

void PauseMenu::setExitCallback(std::function<void()> exitClickCallback)
{
	this->exitClickCallback = exitClickCallback;
}

void PauseMenu::onExitConfirm()
{
	NavigationEvents::LoadScene(TitleScreen::getInstance());
}

void PauseMenu::onCloseClick()
{
	if (this->resumeClickCallback != nullptr)
	{
		this->resumeClickCallback();
	}
}

void PauseMenu::onResumeClick()
{
	if (this->resumeClickCallback != nullptr)
	{
		this->resumeClickCallback();
	}
}

void PauseMenu::onOptionsClick()
{
	if (this->optionsClickCallback != nullptr)
	{
		this->optionsClickCallback();
	}
}

void PauseMenu::onExitClick()
{
	if (this->exitClickCallback != nullptr)
	{
		this->exitClickCallback();
	}
}
