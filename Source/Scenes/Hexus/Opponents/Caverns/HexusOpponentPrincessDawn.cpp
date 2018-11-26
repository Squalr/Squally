#include "HexusOpponentPrincessDawn.h"

const std::string HexusOpponentPrincessDawn::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_DAWN";
HexusOpponentPrincessDawn* HexusOpponentPrincessDawn::instance = nullptr;

HexusOpponentPrincessDawn* HexusOpponentPrincessDawn::getInstance()
{
	if (HexusOpponentPrincessDawn::instance == nullptr)
	{
		HexusOpponentPrincessDawn::instance = new HexusOpponentPrincessDawn();
	}

	return HexusOpponentPrincessDawn::instance;
}

HexusOpponentPrincessDawn::HexusOpponentPrincessDawn() : HexusOpponentData(
	EntityResources::Platformer_Environment_Caverns_Npcs_PrincessDawn_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPrincessDawn::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.49f),
	HexusOpponentData::generateDeck(25, 0.49f,
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

HexusOpponentPrincessDawn::~HexusOpponentPrincessDawn()
{
}
