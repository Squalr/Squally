#include "CodeMenu.h"

CodeMenu* CodeMenu::create()
{
	CodeMenu* codeMenu = new CodeMenu();

	codeMenu->autorelease();

	return codeMenu;
}

CodeMenu::CodeMenu()
{
	this->editMap = new std::map<MenuLabel*, HackableCode*>();
	this->codeMenuBackground = Sprite::create(Resources::Menus_HackerModeMenu_CodeMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);
	this->rows = Node::create();
	this->mouseOverMenuHost = Node::create();
	this->codeEditor = CodeEditor::create();

	this->codeEditor->setVisible(false);

	this->addChild(this->codeMenuBackground);
	this->addChild(this->closeButton);
	this->addChild(this->rows);
	this->addChild(this->mouseOverMenuHost);
	this->addChild(this->codeEditor);

	this->initializePositions();
	this->initializeListeners();
}

CodeMenu::~CodeMenu()
{
	delete(this->editMap);
}

void CodeMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeMenuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 336.0f));
	this->rows->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 196.0f));
	this->mouseOverMenuHost->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
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
	this->editMap->clear();
	int index = 0;

	for (auto iterator = hackableObject->codeList->begin(); iterator != hackableObject->codeList->end(); iterator++)
	{
		Node* newRow = Node::create();
		HackableCode* hackableCode = *iterator;

		Label* address = Label::create(HackUtils::hexAddressOf(hackableCode->codePointer, true, true), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* name = Label::create(hackableCode->functionName, Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* byteLength = Label::create(std::to_string(hackableCode->codeOriginalLength), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		MenuLabel* editLabel = MenuLabel::create("Edit", Resources::Fonts_Montserrat_Medium, fontSize);
		Label* bytes = Label::create(HackUtils::arrayOfByteStringOf(hackableCode->codePointer, hackableCode->codeOriginalLength, 6), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* refData = Label::create(">>", Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);

		address->setPosition(Vec2(-540.0f, spacing * index));
		name->setPosition(Vec2(-280.0f, spacing * index));
		byteLength->setPosition(Vec2(-80.0f, spacing * index));
		editLabel->setPosition(Vec2(32.0f, spacing * index));
		bytes->setPosition(Vec2(252.0f, spacing * index));
		refData->setPosition(Vec2(536.0f, spacing * index));

		MouseOverPanel* addressMouseOver = this->constructAddressMouseOver(hackableCode, address);
		MouseOverPanel* nameMouseOver = this->constructNameMouseOver(hackableCode, name);
		MouseOverPanel* byteLengthMouseOver = this->constructByteLengthMouseOver(hackableCode, byteLength);
		MouseOverPanel* bytesMouseOver = this->constructBytesMouseOver(hackableCode, bytes);

		newRow->addChild(addressMouseOver);
		newRow->addChild(nameMouseOver);
		newRow->addChild(editLabel);
		newRow->addChild(byteLengthMouseOver);
		newRow->addChild(bytesMouseOver);
		newRow->addChild(refData);

		editLabel->setCallback(CC_CALLBACK_1(CodeMenu::onCodeEditClick, this));

		this->editMap->insert_or_assign(editLabel, hackableCode);
		this->rows->addChild(newRow);

		index++;
	}

	this->setVisible(true);
	Utils::focus(this);
}

void CodeMenu::onCodeEditClick(MenuLabel* menuLabel)
{
	HackableCode* hackableCode = this->editMap->at(menuLabel);

	this->codeEditor->open(hackableCode);
}

void CodeMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}

MouseOverPanel* CodeMenu::constructAddressMouseOver(HackableCode* hackableCode, Label* address)
{
	const Size panelSize = Size(320.0f, 320.0f);

	const float fontSize = 24.0f;

	Node* addressMouseOverContent = Node::create();

	Label* addressDescription = Label::create("Address: " + address->getString(), Resources::Fonts_Montserrat_Medium, fontSize);
	Label* addressAttributes = Label::create("This address is static.", Resources::Fonts_Montserrat_Medium, fontSize);

	addressDescription->setPosition(0.0f, panelSize.height / 2 - 32.0f);
	addressAttributes->setPosition(0.0f, panelSize.height / 2 - 32.0f - fontSize - 8.0f);

	addressMouseOverContent->addChild(addressDescription);
	addressMouseOverContent->addChild(addressAttributes);

	return MouseOverPanel::create(address, addressMouseOverContent, mouseOverMenuHost, Size(320.0f, 320.0f));
}

MouseOverPanel* CodeMenu::constructNameMouseOver(HackableCode* hackableCode, Label* name)
{
	const Size panelSize = Size(320.0f, 320.0f);

	const float fontSize = 24.0f;

	Node* nameMouseOverContent = Node::create();

	Label* nameDescription = Label::create("Name: " + name->getString(), Resources::Fonts_Montserrat_Medium, fontSize);

	nameDescription->setPosition(0.0f, panelSize.height / 2 - 32.0f);

	nameMouseOverContent->addChild(nameDescription);

	return MouseOverPanel::create(name, nameMouseOverContent, mouseOverMenuHost, Size(320.0f, 320.0f));
}

MouseOverPanel* CodeMenu::constructByteLengthMouseOver(HackableCode* hackableCode, Label* byteLength)
{
	const Size panelSize = Size(320.0f, 320.0f);

	const float fontSize = 24.0f;

	Node* byteLengthMouseOverContent = Node::create();

	Label* byteLengthDescription = Label::create("Byte Length: " + byteLength->getString(), Resources::Fonts_Montserrat_Medium, fontSize);

	byteLengthDescription->setPosition(0.0f, panelSize.height / 2 - 32.0f);

	byteLengthMouseOverContent->addChild(byteLengthDescription);

	return MouseOverPanel::create(byteLength, byteLengthMouseOverContent, mouseOverMenuHost, Size(320.0f, 320.0f));
}

MouseOverPanel* CodeMenu::constructBytesMouseOver(HackableCode* hackableCode, Label* bytes)
{
	const Size panelSize = Size(320.0f, 320.0f);

	const float fontSize = 24.0f;

	Node* bytesMouseOverContent = Node::create();

	Label* bytesDescription = Label::create("Bytes: " + bytes->getString(), Resources::Fonts_Montserrat_Medium, fontSize);

	bytesDescription->setPosition(0.0f, panelSize.height / 2 - 32.0f);

	bytesMouseOverContent->addChild(bytesDescription);

	return MouseOverPanel::create(bytes, bytesMouseOverContent, mouseOverMenuHost, Size(480.0f, 320.0f));
}
