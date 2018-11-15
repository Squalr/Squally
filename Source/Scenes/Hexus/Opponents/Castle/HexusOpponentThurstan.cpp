#include "HexusOpponentThurstan.h"

const std::string HexusOpponentThurstan::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THURSTAN";
HexusOpponentThurstan* HexusOpponentThurstan::instance = nullptr;

HexusOpponentThurstan* HexusOpponentThurstan::getInstance()
{
	if (HexusOpponentThurstan::instance == nullptr)
	{
		HexusOpponentThurstan::instance = new HexusOpponentThurstan();
	}

	return HexusOpponentThurstan::instance;
}

HexusOpponentThurstan::HexusOpponentThurstan() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_Thurstan_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentThurstan::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.52f),
	HexusOpponentData::generateDeck(25, 0.52f,
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

HexusOpponentThurstan::~HexusOpponentThurstan()
{
}
