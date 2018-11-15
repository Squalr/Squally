#include "HexusOpponentChiron.h"

const std::string HexusOpponentChiron::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CHIRON";
HexusOpponentChiron* HexusOpponentChiron::instance = nullptr;

HexusOpponentChiron* HexusOpponentChiron::getInstance()
{
	if (HexusOpponentChiron::instance == nullptr)
	{
		HexusOpponentChiron::instance = new HexusOpponentChiron();
	}

	return HexusOpponentChiron::instance;
}

HexusOpponentChiron::HexusOpponentChiron() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Chiron_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-40.0f, -24.0f),
	HexusOpponentChiron::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.35f),
	HexusOpponentData::generateDeck(25, 0.35f,
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

HexusOpponentChiron::~HexusOpponentChiron()
{
}
