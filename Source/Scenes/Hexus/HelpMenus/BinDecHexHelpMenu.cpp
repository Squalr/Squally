#include "BinDecHexHelpMenu.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Strings/Hexus/BinHeader.h"
#include "Strings/Hexus/DecHeader.h"
#include "Strings/Hexus/HexHeader.h"

using namespace cocos2d;

BinDecHexHelpMenu* BinDecHexHelpMenu::create()
{
	BinDecHexHelpMenu* instance = new BinDecHexHelpMenu();

	instance->autorelease();

	return instance;
}

BinDecHexHelpMenu::BinDecHexHelpMenu()
{
	this->binCard = nullptr;
	this->decCard = nullptr;
	this->hexCard = nullptr;
	this->binCardNode = Node::create();
	this->decCardNode = Node::create();
	this->hexCardNode = Node::create();
	this->equalsLabelLeft = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, ConstantString::create("="));
	this->equalsLabelRight = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, ConstantString::create("="));
	this->binHeader = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Hexus_BinHeader::create());
	this->decHeader = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Hexus_DecHeader::create());
	this->hexHeader = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Hexus_HexHeader::create());

	this->equalsLabelLeft->enableOutline(Color4B::BLACK, 4);
	this->equalsLabelRight->enableOutline(Color4B::BLACK, 4);
	this->binHeader->enableOutline(Color4B::BLACK, 3);
	this->decHeader->enableOutline(Color4B::BLACK, 3);
	this->hexHeader->enableOutline(Color4B::BLACK, 3);

	this->binHeader->setTextColor(Card::binaryColor);
	this->decHeader->setTextColor(Card::decimalColor);
	this->hexHeader->setTextColor(Card::hexColor);

	this->addChild(this->binCardNode);
	this->addChild(this->decCardNode);
	this->addChild(this->hexCardNode);
	this->addChild(this->equalsLabelLeft);
	this->addChild(this->equalsLabelRight);
	this->addChild(this->binHeader);
	this->addChild(this->decHeader);
	this->addChild(this->hexHeader);
}

BinDecHexHelpMenu::~BinDecHexHelpMenu()
{
}

void BinDecHexHelpMenu::onEnter()
{
	super::onEnter();
}

void BinDecHexHelpMenu::initializePositions()
{
	super::initializePositions();

	this->binHeader->setPosition(Vec2(-256.0f, 144.0f));
	this->decHeader->setPosition(Vec2(0.0f, 144.0f));
	this->hexHeader->setPosition(Vec2(256.0f, 144.0f));
	this->binCardNode->setPosition(Vec2(-256.0f, 0.0f));
	this->decCardNode->setPosition(Vec2(0.0f, 0.0f));
	this->hexCardNode->setPosition(Vec2(256.0f, 0.0f));
	this->equalsLabelLeft->setPosition(Vec2(-128.0f, 0.0f));
	this->equalsLabelRight->setPosition(Vec2(128.0f, 0.0f));
}

void BinDecHexHelpMenu::initializeListeners()
{
	super::initializeListeners();
}

void BinDecHexHelpMenu::open(Card* card)
{
	this->setVisible(true);
	
	if (this->binCard != nullptr)
	{
		this->binCardNode->removeChild(this->binCard);
		this->binCard = nullptr;
	}
	
	if (this->decCard != nullptr)
	{
		this->decCardNode->removeChild(this->decCard);
		this->decCard = nullptr;
	}

	if (this->hexCard != nullptr)
	{
		this->hexCardNode->removeChild(this->hexCard);
		this->hexCard = nullptr;
	}

	switch(card->getOriginalAttack())
	{
		default:
		case 0:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary0));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal0));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex0));
			break;
		}
		case 1:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary1));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal1));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex1));
			break;
		}
		case 2:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary2));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal2));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex2));
			break;
		}
		case 3:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary3));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal3));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex3));
			break;
		}
		case 4:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary4));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal4));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex4));
			break;
		}
		case 5:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary5));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal5));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex5));
			break;
		}
		case 6:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary6));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal6));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex6));
			break;
		}
		case 7:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary7));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal7));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex7));
			break;
		}
		case 8:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary8));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal8));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex8));
			break;
		}
		case 9:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary9));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal9));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex9));
			break;
		}
		case 10:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary10));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal10));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex10));
			break;
		}
		case 11:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary11));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal11));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex11));
			break;
		}
		case 12:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary12));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal12));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex12));
			break;
		}
		case 13:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary13));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal13));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex13));
			break;
		}
		case 14:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary14));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal14));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex14));
			break;
		}
		case 15:
		{
			this->binCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary15));
			this->decCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal15));
			this->hexCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex15));
			break;
		}
	}

	this->binCard->setScale(0.6f);
	this->decCard->setScale(0.6f);
	this->hexCard->setScale(0.6f);
	this->binCard->disableInteraction();
	this->decCard->disableInteraction();
	this->hexCard->disableInteraction();
	this->binCard->reveal();
	this->decCard->reveal();
	this->hexCard->reveal();
	
	this->binCardNode->addChild(this->binCard);
	this->decCardNode->addChild(this->decCard);
	this->hexCardNode->addChild(this->hexCard);
}
