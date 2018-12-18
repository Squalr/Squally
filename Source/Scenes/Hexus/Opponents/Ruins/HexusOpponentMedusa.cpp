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
	EntityResources::Enemies_Medusa_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -24.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentMedusa::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.28f),
	HexusOpponentData::generateDeck(25, 0.28f,
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

HexusOpponentMedusa::~HexusOpponentMedusa()
{
}
