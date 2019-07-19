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
	this->pauseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Pause::create());
	this->newButtonsNode = Node::create();
	this->addedButtons = std::vector<ClickableTextNode*>();
	this->resumeClickCallback = nullptr;
	this->optionsClickCallback = nullptr;
	this->exitClickCallback = nullptr;

	LocalizedLabel*	resumeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Resume::create());
	LocalizedLabel*	resumeLabelHover = resumeLabel->clone();

	LocalizedLabel*	optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Options_Options::create());
	LocalizedLabel*	optionsLabelHover = optionsLabel->clone();

	LocalizedLabel*	exitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_QuitToTitle::create());
	LocalizedLabel*	exitLabelHover = exitLabel->clone();

	resumeLabel->enableOutline(Color4B::BLACK, 2);
	resumeLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	resumeLabel->enableGlow(Color4B::BLACK);
	optionsLabel->enableOutline(Color4B::BLACK, 2);
	optionsLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	optionsLabel->enableGlow(Color4B::BLACK);
	exitLabel->enableOutline(Color4B::BLACK, 2);
	exitLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	exitLabel->enableGlow(Color4B::BLACK);

	resumeLabelHover->enableOutline(Color4B::BLACK, 2);
	resumeLabelHover->setTextColor(Color4B::YELLOW);
	resumeLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	resumeLabelHover->enableGlow(Color4B::ORANGE);
	optionsLabelHover->enableOutline(Color4B::BLACK, 2);
	optionsLabelHover->setTextColor(Color4B::YELLOW);
	optionsLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	optionsLabelHover->enableGlow(Color4B::ORANGE);
	exitLabelHover->enableOutline(Color4B::BLACK, 2);
	exitLabelHover->setTextColor(Color4B::YELLOW);
	exitLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	exitLabelHover->enableGlow(Color4B::ORANGE);

	this->resumeButton = ClickableTextNode::create(
		resumeLabel,
		resumeLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->optionsButton = ClickableTextNode::create(
		optionsLabel,
		optionsLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->exitButton = ClickableTextNode::create(
		exitLabel,
		exitLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->pauseLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->pauseLabel->enableGlow(Color4B::BLACK);
	
	this->addChild(this->pauseWindow);
	this->addChild(this->pauseLabel);
	this->addChild(this->closeButton);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);
	this->addChild(this->newButtonsNode);
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

	for (auto it = this->addedButtons.begin(); it != this->addedButtons.end(); it++)
	{
		GameUtils::fadeInObject(*it, delay, duration);
	}
}

void PauseMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->pauseWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->pauseLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 204.0f, visibleSize.height / 2.0f + 392.0f));
	this->resumeButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 104.0f + 128.0f));
	this->optionsButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 104.0f));
	this->newButtonsNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 104.0f - 128.0f));
	this->exitButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 256.0f));
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

ClickableTextNode* PauseMenu::addNewButton(LocalizedString* text)
{
	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);
	LocalizedLabel*	labelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text == nullptr ? nullptr : text->clone());

	labelSelected->enableOutline(Color4B::BLACK, 2);
	label->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	label->enableGlow(Color4B::BLACK);

	labelSelected->enableOutline(Color4B::BLACK, 2);
	labelSelected->setTextColor(Color4B::YELLOW);
	labelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	labelSelected->enableGlow(Color4B::ORANGE);

	ClickableTextNode* newButton = ClickableTextNode::create(
		label,
		labelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->addedButtons.push_back(newButton);
	this->newButtonsNode->addChild(newButton);

	newButton->setPositionY(float(this->addedButtons.size() - 1) * -128.0f);

	return newButton;
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
