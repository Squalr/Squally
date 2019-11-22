#include "DifficultySelectMenu.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cipher/CipherPuzzleData.h"

#include "Resources/CipherResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/BonusItem.h"
#include "Strings/Cipher/Cipher.h"
#include "Strings/Cipher/Easy.h"
#include "Strings/Cipher/Hard.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

DifficultySelectMenu* DifficultySelectMenu::create()
{
	DifficultySelectMenu* instance = new DifficultySelectMenu();

	instance->autorelease();

	return instance;
}

DifficultySelectMenu::DifficultySelectMenu()
{
	this->panel = Sprite::create(CipherResources::CipherDifficultyPanel);
	this->cipherLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Cipher_Cipher::create());
	this->bonusMessage = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_BonusItem::create());
	LocalizedLabel*	easyLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Easy::create());
	LocalizedLabel*	easyLabelHover = easyLabel->clone();
	LocalizedLabel*	hardLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Hard::create());
	LocalizedLabel*	hardLabelHover = hardLabel->clone();
	LocalizedLabel*	quitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	quitLabelHover = quitLabel->clone();

	this->cipherLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->cipherLabel->enableGlow(Color4B::BLACK);
	this->bonusMessage->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->bonusMessage->enableGlow(Color4B::BLACK);
	easyLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	easyLabel->enableGlow(Color4B::BLACK);
	hardLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	hardLabel->enableGlow(Color4B::BLACK);
	quitLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	quitLabel->enableGlow(Color4B::BLACK);

	easyLabelHover->setColor(Color3B::YELLOW);
	easyLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	easyLabelHover->enableGlow(Color4B::ORANGE);
	hardLabelHover->setColor(Color3B::YELLOW);
	hardLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	hardLabelHover->enableGlow(Color4B::ORANGE);
	quitLabelHover->setColor(Color3B::YELLOW);
	quitLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	quitLabelHover->enableGlow(Color4B::ORANGE);

	this->easyButton = ClickableTextNode::create(
		easyLabel,
		easyLabelHover,
		CipherResources::Buttons_TestRunButton,
		CipherResources::Buttons_TestRunButtonSelected
	);
	this->hardButton = ClickableTextNode::create(
		hardLabel,
		hardLabelHover,
		CipherResources::Buttons_HardButton,
		CipherResources::Buttons_HardButtonSelected
	);
	this->cancelButton = ClickableTextNode::create(
		quitLabel,
		quitLabelHover,
		CipherResources::Buttons_QuitButton,
		CipherResources::Buttons_QuitButtonSelected
	);

	this->addChild(this->panel);
	this->addChild(this->cipherLabel);
	this->addChild(this->bonusMessage);
	this->addChild(this->easyButton);
	this->addChild(this->hardButton);
	this->addChild(this->cancelButton);
}

DifficultySelectMenu::~DifficultySelectMenu()
{
}

void DifficultySelectMenu::onEnter()
{
	super::onEnter();
}

void DifficultySelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->panel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->bonusMessage->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 144.0f));
	this->cipherLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 294.0f));
	this->easyButton->setPosition(Vec2(visibleSize.width / 2.0f - 192.0f, visibleSize.height / 2.0f - 256.0f));
	this->hardButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 256.0f));
	this->cancelButton->setPosition(Vec2(visibleSize.width / 2.0f + 192.0f, visibleSize.height / 2.0f - 256.0f));
}

void DifficultySelectMenu::initializeListeners()
{
	super::initializeListeners();
}

void DifficultySelectMenu::show(CipherPuzzleData* cipherPuzzleData, std::function<void()> onEasySelect, std::function<void()> onHardSelect, std::function<void()> onCancelSelect)
{
	this->setVisible(true);
	
	if (!cipherPuzzleData->hasHardMode() && onEasySelect != nullptr)
	{
		this->setVisible(false);

		this->defer([=]()
		{
			onEasySelect();
		});
		
		return;
	}

	this->easyButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (onEasySelect != nullptr)
		{
			onEasySelect();
			this->setVisible(false);
		}
	});

	this->hardButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (onHardSelect != nullptr)
		{
			onHardSelect();
			this->setVisible(false);
		}
	});

	this->cancelButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (onCancelSelect != nullptr)
		{
			onCancelSelect();
			this->setVisible(false);
		}
	});
}
