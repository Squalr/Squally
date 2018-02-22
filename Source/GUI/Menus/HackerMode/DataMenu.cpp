#include "DataMenu.h"

DataMenu* DataMenu::create()
{
	DataMenu* dataMenu = new DataMenu();

	dataMenu->autorelease();

	return dataMenu;
}

DataMenu::DataMenu()
{
	this->dataMenuBackground = Sprite::create(Resources::Menus_HackerModeMenu_EmptyFullScreenMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);
	this->rows = Node::create();

	this->addChild(this->dataMenuBackground);
	this->addChild(this->closeButton);
	this->addChild(this->rows);

	this->initializePositions();
	this->initializeListeners();
}

DataMenu::~DataMenu()
{
}

void DataMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->dataMenuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 336.0f));
	this->rows->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 196.0f));
}

void DataMenu::open(HackableObject* hackableObject)
{
	const float spacing = -36.0f;
	const float fontSize = 24.0f;

	this->rows->removeAllChildren();
	int index = 0;

	for (auto iterator = hackableObject->dataList->begin(); iterator != hackableObject->dataList->end(); iterator++)
	{
		Node* newRow = Node::create();
		HackableData* hackableData = *iterator;

		Label* address = Label::create(HackUtils::hexAddressOf(hackableData->dataPointer, true, true), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* name = Label::create(hackableData->variableName, Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* dataType = Label::create(HackUtils::dataTypeToString(hackableData->dataType), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* value = Label::create(HackUtils::valueStringOf(hackableData->dataPointer, hackableData->dataType), Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);
		Label* refCode = Label::create(">>", Resources::Fonts_Montserrat_Medium, fontSize, Size::ZERO, TextHAlignment::CENTER);

		address->setPosition(Vec2(-384.0f, spacing * index));
		name->setPosition(Vec2(-160.0f, spacing * index));
		dataType->setPosition(Vec2(72.0f, spacing * index));
		value->setPosition(Vec2(292.0f, spacing * index));
		refCode->setPosition(Vec2(536.0f, spacing * index));

		newRow->addChild(address);
		newRow->addChild(name);
		newRow->addChild(dataType);
		newRow->addChild(value);
		newRow->addChild(refCode);

		this->rows->addChild(newRow);

		index++;
	}

	this->setVisible(true);
	GameUtils::focus(this);
}

void DataMenu::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(DataMenu::onClose, this));
}

void DataMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	GameUtils::focus(this->getParent());
}
