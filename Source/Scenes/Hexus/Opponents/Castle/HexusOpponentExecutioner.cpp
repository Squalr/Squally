#include "HexusOpponentExecutioner.h"

const std::string HexusOpponentExecutioner::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EXECUTIONER";
HexusOpponentExecutioner* HexusOpponentExecutioner::instance = nullptr;

HexusOpponentExecutioner* HexusOpponentExecutioner::getInstance()
{
	if (HexusOpponentExecutioner::instance == nullptr)
	{
		HexusOpponentExecutioner::instance = new HexusOpponentExecutioner();
	}

	return HexusOpponentExecutioner::instance;
}

HexusOpponentExecutioner::HexusOpponentExecutioner() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Enemies_Executioner_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.3f,
	Vec2(-32.0f, -160.0f),
	Vec2(-32.0f, -160.0f),
	HexusOpponentExecutioner::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentExecutioner::~HexusOpponentExecutioner()
{
}
