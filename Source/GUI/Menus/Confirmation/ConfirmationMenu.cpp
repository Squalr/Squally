#include "ConfirmationMenu.h"

ConfirmationMenu * ConfirmationMenu::create(std::string confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback)
{
	ConfirmationMenu* pauseMenu = new ConfirmationMenu(confirmationMessage, confirmCallback, cancelCallback);

	pauseMenu->autorelease();

	return pauseMenu;
}

ConfirmationMenu::ConfirmationMenu(std::string confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback)
{
	this->onConfirmCallback = confirmCallback;
	this->onCancelCallback = cancelCallback;

	this->background = Node::create();
	this->pauseWindow = Sprite::create(Resources::Menus_ConfirmMenu_ConfirmMenuWindow);
	this->closeButton = MenuSprite::create(Sprite::create(Resources::Menus_Buttons_CloseButton), Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);
	this->cancelButton = MenuSprite::create(Sprite::create(Resources::Menus_Buttons_CancelButton), Resources::Menus_Buttons_CancelButtonHover, Resources::Menus_Buttons_CancelButtonClick);
	this->confirmButton = MenuSprite::create(Sprite::create(Resources::Menus_Buttons_AcceptButton), Resources::Menus_Buttons_AcceptButtonHover, Resources::Menus_Buttons_AcceptButtonClick);
	this->confirmationLabel = Label::create(confirmationMessage, Resources::Fonts_Montserrat_Medium, 20);

	this->cancelButton->setClickCallback(CC_CALLBACK_1(ConfirmationMenu::onCancelClick, this));
	this->confirmButton->setClickCallback(CC_CALLBACK_1(ConfirmationMenu::onConfirmClick, this));

	this->closeButton->setClickCallback(CC_CALLBACK_1(ConfirmationMenu::onCloseClick, this));
	this->closeButton->setClickSound(Resources::Sounds_ClickBack1);

	this->addChild(this->background);
	this->addChild(this->pauseWindow);
	this->addChild(this->closeButton);
	this->addChild(this->cancelButton);
	this->addChild(this->confirmButton);
	this->addChild(this->confirmationLabel);

	this->setFadeSpeed(0.0f);
}

ConfirmationMenu::~ConfirmationMenu()
{
}

void ConfirmationMenu::onEnter()
{
	FadeScene::onEnter();

	this->background->addChild(MenuBackground::claimInstance());

	this->initializePositions();

	this->addChild(Mouse::claimInstance());
}

void ConfirmationMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->pauseWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 136.0f, origin.y + visibleSize.height / 2 + 124.0f));
	this->confirmationLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 32.0f));
	this->cancelButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - 96.0f, origin.y + visibleSize.height / 2 - 64.0f));
	this->confirmButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 96.0f, origin.y + visibleSize.height / 2 - 64.0f));

	MenuBackground::getInstance()->initializePositions();
}

void ConfirmationMenu::onCloseClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();

	if (this->onCancelCallback != nullptr)
	{
		this->onCancelCallback();
	}
}

void ConfirmationMenu::onCancelClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();

	if (this->onCancelCallback != nullptr)
	{
		this->onCancelCallback();
	}
}

void ConfirmationMenu::onConfirmClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();

	if (this->onConfirmCallback != nullptr)
	{
		this->onConfirmCallback();
	}
}
