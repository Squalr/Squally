#include "HexusOpponentGoblinWarriorPig.h"

const std::string HexusOpponentGoblinWarriorPig::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_WARRIOR_PIG";
HexusOpponentGoblinWarriorPig* HexusOpponentGoblinWarriorPig::instance = nullptr;

HexusOpponentGoblinWarriorPig* HexusOpponentGoblinWarriorPig::getInstance()
{
	if (HexusOpponentGoblinWarriorPig::instance == nullptr)
	{
		HexusOpponentGoblinWarriorPig::instance = new HexusOpponentGoblinWarriorPig();
	}

	return HexusOpponentGoblinWarriorPig::instance;
}

HexusOpponentGoblinWarriorPig::HexusOpponentGoblinWarriorPig() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_GoblinWarriorPig_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -32.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentGoblinWarriorPig::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.105f,
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

HexusOpponentGoblinWarriorPig::~HexusOpponentGoblinWarriorPig()
{
}
