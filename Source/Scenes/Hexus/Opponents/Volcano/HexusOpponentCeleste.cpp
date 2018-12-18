#include "HexusOpponentCeleste.h"

const std::string HexusOpponentCeleste::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CELESTE";
HexusOpponentCeleste* HexusOpponentCeleste::instance = nullptr;

HexusOpponentCeleste* HexusOpponentCeleste::getInstance()
{
	if (HexusOpponentCeleste::instance == nullptr)
	{
		HexusOpponentCeleste::instance = new HexusOpponentCeleste();
	}

	return HexusOpponentCeleste::instance;
}

HexusOpponentCeleste::HexusOpponentCeleste() : HexusOpponentData(
	EntityResources::Npcs_DaemonsHallow_Celeste_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentCeleste::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.73f),
	HexusOpponentData::generateDeck(25, 0.73f,
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

HexusOpponentCeleste::~HexusOpponentCeleste()
{
}
