#include "HexusOpponentGoblinGruntBoar.h"

const std::string HexusOpponentGoblinGruntBoar::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_GRUNT_BOAR";
HexusOpponentGoblinGruntBoar* HexusOpponentGoblinGruntBoar::instance = nullptr;

HexusOpponentGoblinGruntBoar* HexusOpponentGoblinGruntBoar::getInstance()
{
	if (HexusOpponentGoblinGruntBoar::instance == nullptr)
	{
		HexusOpponentGoblinGruntBoar::instance = new HexusOpponentGoblinGruntBoar();
	}

	return HexusOpponentGoblinGruntBoar::instance;
}

HexusOpponentGoblinGruntBoar::HexusOpponentGoblinGruntBoar() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_GoblinGruntBoar_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -32.0f),
	Vec2(-16.0f, -56.0f),
	HexusOpponentGoblinGruntBoar::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.125f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentGoblinGruntBoar::~HexusOpponentGoblinGruntBoar()
{
}
