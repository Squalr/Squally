#include "HexusOpponentMedusa.h"

const std::string HexusOpponentMedusa::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MEDUSA";
HexusOpponentMedusa* HexusOpponentMedusa::instance = nullptr;

HexusOpponentMedusa* HexusOpponentMedusa::getInstance()
{
	if (HexusOpponentMedusa::instance == nullptr)
	{
		HexusOpponentMedusa::instance = new HexusOpponentMedusa();
	}

	return HexusOpponentMedusa::instance;
}

HexusOpponentMedusa::HexusOpponentMedusa() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_Medusa_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.85f,
	Vec2(-48.0f, -24.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentMedusa::OpponentSaveKey,
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

HexusOpponentMedusa::~HexusOpponentMedusa()
{
}
