#include "CodeMenu.h"

const float CodeMenu::activeColumnOffset = -704.0f;
const float CodeMenu::addressColumnOffset = -480.0f;
const float CodeMenu::functionNameColumnOffset = 0.0f;
const float CodeMenu::dataReferencesColumnOffset = 608.0f;
const Color4B CodeMenu::defaultHeaderColor = Color4B(59, 92, 97, 192);
const Color4B CodeMenu::defaultRowSelectionColor = Color4B(39, 58, 61, 192);

CodeMenu* CodeMenu::create()
{
	CodeMenu* codeMenu = new CodeMenu();

	codeMenu->autorelease();

	return codeMenu;
}

CodeMenu::CodeMenu()
{
	this->activeHackableObject = nullptr;
	this->checkboxMap = new  std::map<CCheckbox*, HackableCode*>();
	this->editMap = new std::map<MenuSprite*, HackableCode*>();
	this->codeMenuBackground = Sprite::create(Resources::Menus_HackerModeMenu_EmptyFullScreenMenu);
	this->codeMenuTitle = MenuLabel::create("Code", Resources::Fonts_Montserrat_Medium, 32);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);
	this->header = Node::create();
	this->rows = Node::create();
	this->mouseOverMenuHost = Node::create();
	this->codeEditor = CodeEditor::create();

	const float fontSize = 32.0f;

	LayerColor* headerBackground = LayerColor::create(CodeMenu::defaultHeaderColor, 1600.0f, 48.0f);
	Label* active = Label::create("Active", Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
	Label* address = Label::create("Address", Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
	Label* name = Label::create("Function Name", Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
	Label* refData = Label::create("Data References", Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);

	headerBackground->setPosition(Vec2(-headerBackground->getContentSize().width / 2.0f, -headerBackground->getContentSize().height / 2.0f));
	active->setPosition(Vec2(CodeMenu::activeColumnOffset, 0.0f));
	address->setPosition(Vec2(CodeMenu::addressColumnOffset, 0.0f));
	name->setPosition(Vec2(CodeMenu::functionNameColumnOffset, 0.0f));
	refData->setPosition(Vec2(CodeMenu::dataReferencesColumnOffset, 0.0f));

	this->header->addChild(headerBackground);
	this->header->addChild(active);
	this->header->addChild(address);
	this->header->addChild(name);
	this->header->addChild(refData);

	this->codeEditor->setVisible(false);

	this->addChild(this->codeMenuBackground);
	this->addChild(this->codeMenuTitle);
	this->addChild(this->closeButton);
	this->addChild(this->header);
	this->addChild(this->rows);
	this->addChild(this->mouseOverMenuHost);
	this->addChild(this->codeEditor);

	this->initializePositions();
	this->initializeListeners();
}

CodeMenu::~CodeMenu()
{
	delete(this->checkboxMap);
	delete(this->editMap);
}

void CodeMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeMenuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->codeMenuTitle->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 444.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 848.0f, visibleSize.height / 2.0f + 444.0f));
	this->header->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 256.0f));
	this->rows->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 196.0f));
	this->mouseOverMenuHost->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void CodeMenu::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(CodeMenu::onClose, this));
}

void CodeMenu::open(HackableObject* hackableObject)
{
	this->activeHackableObject = hackableObject;

	this->populateRows();

	this->setVisible(true);

	Utils::focus(this);
}

void CodeMenu::resume()
{
	this->populateRows();

	this->codeMenuBackground->setVisible(true);
	this->codeMenuTitle->setVisible(true);
	this->closeButton->setVisible(true);
	this->rows->setVisible(true);
	this->mouseOverMenuHost->setVisible(true);

	Node::resume();
}

void CodeMenu::populateRows()
{
	const float spacing = 4.0f;
	const float fontSize = 24.0f;
	const float rowWidth = 1600.0f;
	const float rowHeight = 48.0f;

	this->rows->removeAllChildren();
	this->checkboxMap->clear();
	this->editMap->clear();
	int index = 0;

	if (this->activeHackableObject != nullptr)
	{
		for (auto iterator = this->activeHackableObject->codeList->begin(); iterator != this->activeHackableObject->codeList->end(); iterator++)
		{
			Node* newRow = Node::create();
			HackableCode* hackableCode = *iterator;

			MenuSprite* uncheckedMenuSprite = MenuSprite::create(Resources::Menus_OptionsMenu_CheckboxEmpty, Resources::Menus_OptionsMenu_CheckboxHover, Resources::Menus_OptionsMenu_CheckboxHover);
			MenuSprite* checkedMenuSprite = MenuSprite::create(Resources::Menus_OptionsMenu_CheckboxSelected, Resources::Menus_OptionsMenu_CheckboxSelected, Resources::Menus_OptionsMenu_CheckboxSelected);
			CCheckbox* isActiveCheckbox = CCheckbox::create(uncheckedMenuSprite, checkedMenuSprite, ConfigManager::getIsFullScreen(), CC_CALLBACK_2(CodeMenu::onActivated, this));

			LayerColor* normalBackground = LayerColor::create(Color4B(0, 0, 0, 0), rowWidth, rowHeight);
			LayerColor* selectedBackground = LayerColor::create(CodeMenu::defaultRowSelectionColor, rowWidth, rowHeight);
			LayerColor* clickedBackground = LayerColor::create(CodeMenu::defaultRowSelectionColor, rowWidth, rowHeight);
			MenuSprite* rowSelection = MenuSprite::create(normalBackground, selectedBackground, clickedBackground);
			Label* address = Label::create(HackUtils::hexAddressOf(hackableCode->codePointer, true, true), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
			Label* name = Label::create(hackableCode->functionName, Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
			MenuSprite* refData = MenuSprite::create(Resources::Menus_HackerModeMenu_ExitRightButton, Resources::Menus_HackerModeMenu_ExitRightButtonHover, Resources::Menus_HackerModeMenu_ExitRightButtonClick);

			rowSelection->setPosition(Vec2(-rowSelection->getContentSize().width / 2.0f, (-rowHeight - spacing) * index - rowSelection->getContentSize().height / 2.0f));
			isActiveCheckbox->setPosition(Vec2(CodeMenu::activeColumnOffset, (-rowHeight - spacing)* index));
			address->setPosition(Vec2(CodeMenu::addressColumnOffset, (-rowHeight - spacing)* index));
			name->setPosition(Vec2(CodeMenu::functionNameColumnOffset, (-rowHeight - spacing)* index));
			refData->setPosition(Vec2(CodeMenu::dataReferencesColumnOffset, (-rowHeight - spacing) * index));

			newRow->addChild(rowSelection);
			newRow->addChild(isActiveCheckbox);
			newRow->addChild(address);
			newRow->addChild(name);
			newRow->addChild(refData);

			refData->setClickCallback(CC_CALLBACK_1(CodeMenu::onDataReferencesClick, this));
			rowSelection->setClickCallback(CC_CALLBACK_1(CodeMenu::onCodeEditClick, this));

			this->checkboxMap->insert_or_assign(isActiveCheckbox, hackableCode);
			this->editMap->insert_or_assign(rowSelection, hackableCode);
			this->rows->addChild(newRow);

			index++;
		}
	}
}

bool CodeMenu::onActivated(CCheckbox* checkbox, bool isActivated)
{
	HackableCode* hackableCode = this->checkboxMap->at(checkbox);

	if (isActivated)
	{
		bool activationSuccess = hackableCode->applyCustomCode();

		if (!activationSuccess)
		{
			// TODO: Some sort of warning indicating the activation failed
			return false;
		}
	}
	else
	{
		hackableCode->restoreOriginalCode();
	}

	return isActivated;
}

void CodeMenu::onDataReferencesClick(MenuSprite* menuSprite)
{

}

void CodeMenu::onCodeEditClick(MenuSprite* menuSprite)
{
	HackableCode* hackableCode = this->editMap->at(menuSprite);

	this->codeMenuBackground->setVisible(false);
	this->codeMenuTitle->setVisible(false);
	this->closeButton->setVisible(false);
	this->rows->setVisible(false);
	this->mouseOverMenuHost->setVisible(false);

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
