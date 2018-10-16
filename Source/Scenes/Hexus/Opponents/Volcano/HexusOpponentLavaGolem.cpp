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
	Resources::Entities_Platformer_Environment_Volcano_Enemies_LavaGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -80.0f),
	HexusOpponentLavaGolem::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
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
