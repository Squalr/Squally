#include "HexusOpponentZeus.h"

const std::string HexusOpponentZeus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZEUS";
HexusOpponentZeus* HexusOpponentZeus::instance = nullptr;

HexusOpponentZeus* HexusOpponentZeus::getInstance()
{
	if (HexusOpponentZeus::instance == nullptr)
	{
		HexusOpponentZeus::instance = new HexusOpponentZeus();
	}

	return HexusOpponentZeus::instance;
}

HexusOpponentZeus::HexusOpponentZeus() : HexusOpponentData(
	EntityResources::Platformer_Environment_Ruins_Npcs_Zeus_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(0.0f, -24.0f),
	HexusOpponentZeus::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.275f),
	HexusOpponentData::generateDeck(25, 0.275f,
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

HexusOpponentZeus::~HexusOpponentZeus()
{
}
