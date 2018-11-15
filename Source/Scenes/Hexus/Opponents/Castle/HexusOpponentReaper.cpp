#include "HexusOpponentReaper.h"

const std::string HexusOpponentReaper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_REAPER";
HexusOpponentReaper* HexusOpponentReaper::instance = nullptr;

HexusOpponentReaper* HexusOpponentReaper::getInstance()
{
	if (HexusOpponentReaper::instance == nullptr)
	{
		HexusOpponentReaper::instance = new HexusOpponentReaper();
	}

	return HexusOpponentReaper::instance;
}

HexusOpponentReaper::HexusOpponentReaper() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Enemies_Reaper_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(0.0f, -224.0f),
	Vec2(-16.0f, -256.0f),
	HexusOpponentReaper::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.545f),
	HexusOpponentData::generateDeck(25, 0.545f,
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

HexusOpponentReaper::~HexusOpponentReaper()
{
}
