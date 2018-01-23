#include "CodeMenu.h"

CodeMenu* CodeMenu::create()
{
	CodeMenu* codeMenu = new CodeMenu();

	codeMenu->autorelease();

	return codeMenu;
}

CodeMenu::CodeMenu()
{
	this->codeMenuBackground = Sprite::create(Resources::Menus_HackerModeMenu_CodeMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);
	this->rows = Node::create();

	this->addChild(this->codeMenuBackground);
	this->addChild(this->closeButton);
	this->addChild(this->rows);

	this->initializePositions();
	this->initializeListeners();
}

CodeMenu::~CodeMenu()
{
}

void CodeMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeMenuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 336.0f));
	this->rows->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 196.0f));
}

void CodeMenu::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(CodeMenu::onClose, this));
}

void CodeMenu::open(HackableObject* hackableObject)
{
	const float spacing = -36.0f;
	const float fontSize = 24.0f;

	this->rows->removeAllChildren();
	int index = 0;

	for (auto iterator = hackableObject->codeList->begin(); iterator != hackableObject->codeList->end(); iterator++)
	{
		Node* newRow = Node::create();
		HackableCode* hackableCode = *iterator;

		Label* address = Label::create(HackUtils::hexAddressOf(hackableCode->codePointer, true, true), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* name = Label::create(hackableCode->functionName, Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* byteLength = Label::create(std::to_string(hackableCode->codeOriginalLength), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* bytes = Label::create(HackUtils::arrayOfByteStringOf(hackableCode->codePointer, hackableCode->codeOriginalLength, 6), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* refData = Label::create(">>", Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);

		Node* addressMouseOverContent = Node::create();

		addressMouseOverContent->addChild(Label::create("Swag", Resources::Fonts_Montserrat_Medium, fontSize));

		MouseOverPanel* addressMouseOver = MouseOverPanel::create(address, addressMouseOverContent, Vec2(256.0f, 320.0f));

		addressMouseOver->setPosition(Vec2(-540.0f, spacing * index));
		name->setPosition(Vec2(-280.0f, spacing * index));
		byteLength->setPosition(Vec2(-80.0f, spacing * index));
		bytes->setPosition(Vec2(252.0f, spacing * index));
		refData->setPosition(Vec2(536.0f, spacing * index));

		newRow->addChild(addressMouseOver);
		newRow->addChild(name);
		newRow->addChild(byteLength);
		newRow->addChild(bytes);
		newRow->addChild(refData);

		this->rows->addChild(newRow);

		index++;
	}

	this->setVisible(true);
}

void CodeMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
