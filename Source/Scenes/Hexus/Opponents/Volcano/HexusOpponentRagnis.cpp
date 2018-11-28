#include "HexusOpponentRagnis.h"

const std::string HexusOpponentRagnis::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RAGNIS";
HexusOpponentRagnis* HexusOpponentRagnis::instance = nullptr;

HexusOpponentRagnis* HexusOpponentRagnis::getInstance()
{
	if (HexusOpponentRagnis::instance == nullptr)
	{
		HexusOpponentRagnis::instance = new HexusOpponentRagnis();
	}

	return HexusOpponentRagnis::instance;
}

HexusOpponentRagnis::HexusOpponentRagnis() : HexusOpponentData(
	EntityResources::Environment_Volcano_Npcs_Ragnis_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentRagnis::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.79f),
	HexusOpponentData::generateDeck(25, 0.79f,
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

HexusOpponentRagnis::~HexusOpponentRagnis()
{
}
