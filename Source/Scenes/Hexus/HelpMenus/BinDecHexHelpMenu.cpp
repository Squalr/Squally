#include "BinDecHexHelpMenu.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/HelpMenus/AutoCard.h"

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
	this->binCard = AutoCard::create();
	this->decCard = AutoCard::create();
	this->hexCard = AutoCard::create();
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

	this->binCard->setDisplayType(AutoCard::DisplayType::Binary);
	this->decCard->setDisplayType(AutoCard::DisplayType::Decimal);
	this->hexCard->setDisplayType(AutoCard::DisplayType::Hex);

	this->binCard->setCardScale(0.6f);
	this->decCard->setCardScale(0.6f);
	this->hexCard->setCardScale(0.6f);

	this->addChild(this->binCard);
	this->addChild(this->decCard);
	this->addChild(this->hexCard);
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
	this->binCard->setPosition(Vec2(-256.0f, 0.0f));
	this->decCard->setPosition(Vec2(0.0f, 0.0f));
	this->hexCard->setPosition(Vec2(256.0f, 0.0f));
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

	this->binCard->setAttack(card->getOriginalAttack());
	this->decCard->setAttack(card->getOriginalAttack());
	this->hexCard->setAttack(card->getOriginalAttack());
}
