#include "BinDecHexHelpMenu.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/HelpMenus/ToggleCard.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BinDecHexHelpMenu* BinDecHexHelpMenu::create()
{
	BinDecHexHelpMenu* instance = new BinDecHexHelpMenu();

	instance->autorelease();

	return instance;
}

BinDecHexHelpMenu::BinDecHexHelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_BinDecHex::create(), Size(1200.0f, 0.0f));
	this->binCard = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight);
	this->decCard = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight);
	this->hexCard = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight);
	this->equalsLabelLeft = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, ConstantString::create("="));
	this->equalsLabelRight = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, ConstantString::create("="));
	this->binHeader = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Hexus_BinHeader::create());
	this->decHeader = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Hexus_DecHeader::create());
	this->hexHeader = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Hexus_HexHeader::create());

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->equalsLabelLeft->enableOutline(Color4B::BLACK, 4);
	this->equalsLabelRight->enableOutline(Color4B::BLACK, 4);
	this->binHeader->enableOutline(Color4B::BLACK, 3);
	this->decHeader->enableOutline(Color4B::BLACK, 3);
	this->hexHeader->enableOutline(Color4B::BLACK, 3);

	this->binHeader->setTextColor(Card::BinaryColor);
	this->decHeader->setTextColor(Card::DecimalColor);
	this->hexHeader->setTextColor(Card::HexColor);

	this->binCard->setDisplayType(AutoCard::DisplayType::Binary);
	this->decCard->setDisplayType(AutoCard::DisplayType::Decimal);
	this->hexCard->setDisplayType(AutoCard::DisplayType::Hex);

	this->binCard->setCardScale(0.6f);
	this->decCard->setCardScale(0.6f);
	this->hexCard->setCardScale(0.6f);

	this->addChild(this->description);
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

	this->description->setPosition(Vec2(-1234 / 2.0f + 16.0f, 420.0f));
	this->binHeader->setPosition(Vec2(-352.0f, 144.0f));
	this->decHeader->setPosition(Vec2(0.0f, 144.0f));
	this->hexHeader->setPosition(Vec2(352.0f, 144.0f));
	this->binCard->setPosition(Vec2(-352.0f, 0.0f));
	this->decCard->setPosition(Vec2(0.0f, 0.0f));
	this->hexCard->setPosition(Vec2(352.0f, 0.0f));
	this->equalsLabelLeft->setPosition(Vec2(-176.0f, 0.0f));
	this->equalsLabelRight->setPosition(Vec2(176.0f, 0.0f));
}

void BinDecHexHelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->binCard->setToggleAttackCallback([=]()
	{
		this->decCard->setAttack(binCard->getAttack());
		this->hexCard->setAttack(binCard->getAttack());
	});

	this->decCard->setToggleAttackCallback([=]()
	{
		this->binCard->setAttack(decCard->getAttack());
		this->hexCard->setAttack(decCard->getAttack());
	});

	this->hexCard->setToggleAttackCallback([=]()
	{
		this->binCard->setAttack(hexCard->getAttack());
		this->decCard->setAttack(hexCard->getAttack());
	});
}

void BinDecHexHelpMenu::open(CardData* cardData)
{
	this->setVisible(true);

	this->binCard->setAttack(cardData->getAttack());
	this->decCard->setAttack(cardData->getAttack());
	this->hexCard->setAttack(cardData->getAttack());
}
