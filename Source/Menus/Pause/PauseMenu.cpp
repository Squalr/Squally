#include "PauseMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

PauseMenu* PauseMenu::create()
{
	PauseMenu* instance = new PauseMenu();

	instance->autorelease();

	return instance;
}

PauseMenu::PauseMenu(bool ownerInitialized)
{
	// Do nothing if this flag is set -- the overriding class will instantiate everything
	if (ownerInitialized)
	{
		return;
	}

	this->pauseWindow = Sprite::create(UIResources::Menus_PauseMenu_PauseMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButtonSelected, UIResources::Menus_IngameMenu_CloseButton);
	this->pauseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Pause_Pause::create());
	this->newButtonsNode = Node::create();
	this->addedButtons = std::vector<ClickableTextNode*>();
	this->resumeClickCallback = nullptr;
	this->optionsClickCallback = nullptr;
	this->quitToTitleClickCallback = nullptr;

	LocalizedLabel*	resumeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Pause_Resume::create());
	LocalizedLabel*	resumeLabelSelected = resumeLabel->clone();

	LocalizedLabel*	optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Pause_Options::create());
	LocalizedLabel*	optionsLabelSelected = optionsLabel->clone();

	LocalizedLabel*	quitToTitleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Pause_QuitToTitle::create());
	LocalizedLabel*	quitToTitleLabelSelected = quitToTitleLabel->clone();

	resumeLabel->enableOutline(Color4B::BLACK, 2);
	resumeLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	resumeLabel->enableGlow(Color4B::BLACK);
	optionsLabel->enableOutline(Color4B::BLACK, 2);
	optionsLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	optionsLabel->enableGlow(Color4B::BLACK);
	quitToTitleLabel->enableOutline(Color4B::BLACK, 2);
	quitToTitleLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	quitToTitleLabel->enableGlow(Color4B::BLACK);

	resumeLabelSelected->enableOutline(Color4B::BLACK, 2);
	resumeLabelSelected->setTextColor(Color4B::YELLOW);
	resumeLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	resumeLabelSelected->enableGlow(Color4B::ORANGE);
	optionsLabelSelected->enableOutline(Color4B::BLACK, 2);
	optionsLabelSelected->setTextColor(Color4B::YELLOW);
	optionsLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	optionsLabelSelected->enableGlow(Color4B::ORANGE);
	quitToTitleLabelSelected->enableOutline(Color4B::BLACK, 2);
	quitToTitleLabelSelected->setTextColor(Color4B::YELLOW);
	quitToTitleLabelSelected->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	quitToTitleLabelSelected->enableGlow(Color4B::ORANGE);

	this->resumeButton = ClickableTextNode::create(
		resumeLabel,
		resumeLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->optionsButton = ClickableTextNode::create(
		optionsLabel,
		optionsLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->quitToTitleButton = ClickableTextNode::create(
		quitToTitleLabel,
		quitToTitleLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->pauseLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->pauseLabel->enableGlow(Color4B::BLACK);
	
	this->addChild(this->pauseWindow);
	this->addChild(this->pauseLabel);
	this->addChild(this->closeButton);
	this->addChild(this->resumeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->quitToTitleButton);
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
	GameUtils::fadeInObject(this->quitToTitleButton, delay, duration);

	for (auto next : this->addedButtons)
	{
		GameUtils::fadeInObject(next, delay, duration);
	}
}

void PauseMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->pauseWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->pauseLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 204.0f, visibleSize.height / 2.0f + 392.0f));

	if (this->resumeButton != nullptr)
	{
		this->resumeButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 104.0f + 128.0f));
	}

	this->optionsButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 104.0f));
	this->newButtonsNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 104.0f - 128.0f));
	this->quitToTitleButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 256.0f));
}

void PauseMenu::initializeListeners()
{
	super::initializeListeners();

	if (this->resumeButton != nullptr)
	{
		this->resumeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
		{
			this->close();
		});
	}
	
	this->optionsButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->optionsClickCallback != nullptr)
		{
			this->optionsClickCallback();
		}
	});

	this->quitToTitleButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->quitToTitleClickCallback != nullptr)
		{
			this->quitToTitleClickCallback();
		}
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});
	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		this->close();
	});
}

void PauseMenu::open(std::function<void()> resumeClickCallback)
{
	this->resumeClickCallback = resumeClickCallback;
	this->setVisible(true);

	GameUtils::focus(this);
}

void PauseMenu::close()
{
	this->setVisible(false);

	if (this->resumeClickCallback != nullptr)
	{
		this->resumeClickCallback();
	}
}

void PauseMenu::setOptionsClickCallback(std::function<void()> optionsClickCallback)
{
	this->optionsClickCallback = optionsClickCallback;
}

void PauseMenu::setQuitToTitleClickCallback(std::function<void()> quitToTitleClickCallback)
{
	this->quitToTitleClickCallback = quitToTitleClickCallback;
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
