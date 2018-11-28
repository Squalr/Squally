#include "HexusOpponentLavaGolem.h"

const std::string HexusOpponentLavaGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LAVA_GOLEM";
HexusOpponentLavaGolem* HexusOpponentLavaGolem::instance = nullptr;

HexusOpponentLavaGolem* HexusOpponentLavaGolem::getInstance()
{
	if (HexusOpponentLavaGolem::instance == nullptr)
	{
		HexusOpponentLavaGolem::instance = new HexusOpponentLavaGolem();
	}

	return HexusOpponentLavaGolem::instance;
}

HexusOpponentLavaGolem::HexusOpponentLavaGolem() : HexusOpponentData(
	EntityResources::Environment_Volcano_Enemies_LavaGolem_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -80.0f),
	HexusOpponentLavaGolem::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.705f),
	HexusOpponentData::generateDeck(25, 0.705f,
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

HexusOpponentLavaGolem::~HexusOpponentLavaGolem()
{
}
