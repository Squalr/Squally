#include "HexusOpponentGenie.h"

const std::string HexusOpponentGenie::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GENIE";
HexusOpponentGenie* HexusOpponentGenie::instance = nullptr;

HexusOpponentGenie* HexusOpponentGenie::getInstance()
{
	if (HexusOpponentGenie::instance == nullptr)
	{
		HexusOpponentGenie::instance = new HexusOpponentGenie();
	}

	return HexusOpponentGenie::instance;
}

HexusOpponentGenie::HexusOpponentGenie() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Enemies_Genie_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.3f,
	Vec2(-32.0f, -160.0f),
	Vec2(-16.0f, -192.0f),
	HexusOpponentGenie::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.485f),
	HexusOpponentData::generateDeck(25, 0.485f,
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

HexusOpponentGenie::~HexusOpponentGenie()
{
}
