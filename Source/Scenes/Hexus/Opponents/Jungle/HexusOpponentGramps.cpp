#include "HexusOpponentGramps.h"

const std::string HexusOpponentGramps::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GRAMPS";
HexusOpponentGramps* HexusOpponentGramps::instance = nullptr;

HexusOpponentGramps* HexusOpponentGramps::getInstance()
{
	if (HexusOpponentGramps::instance == nullptr)
	{
		HexusOpponentGramps::instance = new HexusOpponentGramps();
	}

	return HexusOpponentGramps::instance;
}

HexusOpponentGramps::HexusOpponentGramps() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Npcs_Gramps_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentGramps::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentGramps::~HexusOpponentGramps()
{
}
