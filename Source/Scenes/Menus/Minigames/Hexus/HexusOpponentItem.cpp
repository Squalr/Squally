#include "HexusOpponentItem.h"

HexusOpponentItem* HexusOpponentItem::create(std::string description, std::string mapFile, int index, std::function<void(HexusOpponentItem*)> onMouseOver)
{
	HexusOpponentItem* instance = new HexusOpponentItem(description, mapFile, index, onMouseOver);

	instance->autorelease();

	return instance;
}

HexusOpponentItem::HexusOpponentItem(std::string description, std::string mapFile, int index, std::function<void(HexusOpponentItem*)> onMouseOver)
{
	this->frame = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_EnemyFrame);

	this->setContentSize(this->frame->getContentSize());
	this->setCascadeOpacityEnabled(true);

	this->addChild(this->frame);
}

HexusOpponentItem::~HexusOpponentItem()
{
}

void HexusOpponentItem::onTutorialClick(MenuSprite* HexusOpponentItem)
{
	Deck* deck1 = Deck::create(Card::CardStyle::Earth, new std::vector<CardData*>({
			CardData::cardListByName.at(CardData::Binary0),
			CardData::cardListByName.at(CardData::Binary1),
			CardData::cardListByName.at(CardData::Binary2),
			CardData::cardListByName.at(CardData::Binary3),
			CardData::cardListByName.at(CardData::Binary4),
			CardData::cardListByName.at(CardData::Binary5),
			CardData::cardListByName.at(CardData::Binary6),
			CardData::cardListByName.at(CardData::Binary7),
			CardData::cardListByName.at(CardData::Binary8),
			CardData::cardListByName.at(CardData::Binary9),
			CardData::cardListByName.at(CardData::Binary10),
			CardData::cardListByName.at(CardData::Binary11),
			CardData::cardListByName.at(CardData::Binary12),
			CardData::cardListByName.at(CardData::Binary13),
			CardData::cardListByName.at(CardData::Binary14),
			CardData::cardListByName.at(CardData::Binary15),
			CardData::cardListByName.at(CardData::Decimal0),
			CardData::cardListByName.at(CardData::Decimal1),
			CardData::cardListByName.at(CardData::Decimal2),
			CardData::cardListByName.at(CardData::Decimal3),
			CardData::cardListByName.at(CardData::Decimal4),
			CardData::cardListByName.at(CardData::Decimal5),
			CardData::cardListByName.at(CardData::Decimal6),
			CardData::cardListByName.at(CardData::Decimal7),
			CardData::cardListByName.at(CardData::Decimal8),
			CardData::cardListByName.at(CardData::Decimal9),
			CardData::cardListByName.at(CardData::Decimal10),
			CardData::cardListByName.at(CardData::Decimal11),
			CardData::cardListByName.at(CardData::Decimal12),
			CardData::cardListByName.at(CardData::Decimal13),
			CardData::cardListByName.at(CardData::Decimal14),
			CardData::cardListByName.at(CardData::Decimal15),
			CardData::cardListByName.at(CardData::Hex0),
			CardData::cardListByName.at(CardData::Hex1),
			CardData::cardListByName.at(CardData::Hex2),
			CardData::cardListByName.at(CardData::Hex3),
			CardData::cardListByName.at(CardData::Hex4),
			CardData::cardListByName.at(CardData::Hex5),
			CardData::cardListByName.at(CardData::Hex6),
			CardData::cardListByName.at(CardData::Hex7),
			CardData::cardListByName.at(CardData::Hex8),
			CardData::cardListByName.at(CardData::Hex9),
			CardData::cardListByName.at(CardData::Hex10),
			CardData::cardListByName.at(CardData::Hex11),
			CardData::cardListByName.at(CardData::Hex12),
			CardData::cardListByName.at(CardData::Hex13),
			CardData::cardListByName.at(CardData::Hex14),
			CardData::cardListByName.at(CardData::Hex15),
			CardData::cardListByName.at(CardData::ShiftLeft),
			CardData::cardListByName.at(CardData::ShiftRight),
			CardData::cardListByName.at(CardData::LogicalAnd),
			CardData::cardListByName.at(CardData::LogicalOr),
			CardData::cardListByName.at(CardData::LogicalXor),
			CardData::cardListByName.at(CardData::ShiftLeft),
			CardData::cardListByName.at(CardData::ShiftRight),
			CardData::cardListByName.at(CardData::Flip1),
			CardData::cardListByName.at(CardData::Flip2),
			CardData::cardListByName.at(CardData::Flip3),
			CardData::cardListByName.at(CardData::Flip4),
			CardData::cardListByName.at(CardData::BitFlip),
			CardData::cardListByName.at(CardData::BitFlip),
			CardData::cardListByName.at(CardData::BitFlip),
			CardData::cardListByName.at(CardData::BinaryAddition),
			CardData::cardListByName.at(CardData::BinarySubtraction),
		}));

	deck1->retain();

	Deck* deck2 = Deck::create(Card::CardStyle::Earth, new std::vector<CardData*>({
			CardData::cardListByName.at(CardData::Binary0),
			CardData::cardListByName.at(CardData::Binary1),
			CardData::cardListByName.at(CardData::Binary2),
			CardData::cardListByName.at(CardData::Binary3),
			CardData::cardListByName.at(CardData::Binary4),
			CardData::cardListByName.at(CardData::Binary5),
			CardData::cardListByName.at(CardData::Binary6),
			CardData::cardListByName.at(CardData::Binary7),
			CardData::cardListByName.at(CardData::Binary8),
			CardData::cardListByName.at(CardData::Binary9),
			CardData::cardListByName.at(CardData::Binary10),
			CardData::cardListByName.at(CardData::Binary11),
			CardData::cardListByName.at(CardData::Binary12),
			CardData::cardListByName.at(CardData::Binary13),
			CardData::cardListByName.at(CardData::Binary14),
			CardData::cardListByName.at(CardData::Binary15),
			CardData::cardListByName.at(CardData::Decimal0),
			CardData::cardListByName.at(CardData::Decimal1),
			CardData::cardListByName.at(CardData::Decimal2),
			CardData::cardListByName.at(CardData::Decimal3),
			CardData::cardListByName.at(CardData::Decimal4),
			CardData::cardListByName.at(CardData::Decimal5),
			CardData::cardListByName.at(CardData::Decimal6),
			CardData::cardListByName.at(CardData::Decimal7),
			CardData::cardListByName.at(CardData::Decimal8),
			CardData::cardListByName.at(CardData::Decimal9),
			CardData::cardListByName.at(CardData::Decimal10),
			CardData::cardListByName.at(CardData::Decimal11),
			CardData::cardListByName.at(CardData::Decimal12),
			CardData::cardListByName.at(CardData::Decimal13),
			CardData::cardListByName.at(CardData::Decimal14),
			CardData::cardListByName.at(CardData::Decimal15),
			CardData::cardListByName.at(CardData::Hex0),
			CardData::cardListByName.at(CardData::Hex1),
			CardData::cardListByName.at(CardData::Hex2),
			CardData::cardListByName.at(CardData::Hex3),
			CardData::cardListByName.at(CardData::Hex4),
			CardData::cardListByName.at(CardData::Hex5),
			CardData::cardListByName.at(CardData::Hex6),
			CardData::cardListByName.at(CardData::Hex7),
			CardData::cardListByName.at(CardData::Hex8),
			CardData::cardListByName.at(CardData::Hex9),
			CardData::cardListByName.at(CardData::Hex10),
			CardData::cardListByName.at(CardData::Hex11),
			CardData::cardListByName.at(CardData::Hex12),
			CardData::cardListByName.at(CardData::Hex13),
			CardData::cardListByName.at(CardData::Hex14),
			CardData::cardListByName.at(CardData::Hex15),
			CardData::cardListByName.at(CardData::ShiftLeft),
			CardData::cardListByName.at(CardData::ShiftRight),
			CardData::cardListByName.at(CardData::LogicalAnd),
			CardData::cardListByName.at(CardData::LogicalOr),
			CardData::cardListByName.at(CardData::LogicalXor),
			CardData::cardListByName.at(CardData::ShiftLeft),
			CardData::cardListByName.at(CardData::ShiftRight),
			CardData::cardListByName.at(CardData::Flip1),
			CardData::cardListByName.at(CardData::Flip2),
			CardData::cardListByName.at(CardData::Flip3),
			CardData::cardListByName.at(CardData::Flip4),
			CardData::cardListByName.at(CardData::BitFlip),
			CardData::cardListByName.at(CardData::BitFlip),
			CardData::cardListByName.at(CardData::BitFlip),
			CardData::cardListByName.at(CardData::BinaryAddition),
			CardData::cardListByName.at(CardData::BinarySubtraction),
		}));

	deck2->retain();

	HexusEvents::startGame(HexusEvents::HexusGameEventArgs(deck1, deck2));
}

void HexusOpponentItem::onTutorialMouseOver(MenuSprite* HexusOpponentItem)
{
	this->onMouseOverEvent(this);
}
