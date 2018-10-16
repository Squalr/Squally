#include "HexusOpponentErlic.h"

const std::string HexusOpponentErlic::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ERLIC";
HexusOpponentErlic* HexusOpponentErlic::instance = nullptr;

HexusOpponentErlic* HexusOpponentErlic::getInstance()
{
	if (HexusOpponentErlic::instance == nullptr)
	{
		HexusOpponentErlic::instance = new HexusOpponentErlic();
	}

	return HexusOpponentErlic::instance;
}

HexusOpponentErlic::HexusOpponentErlic() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_Elric_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentErlic::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.55f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentErlic::~HexusOpponentErlic()
{
}
