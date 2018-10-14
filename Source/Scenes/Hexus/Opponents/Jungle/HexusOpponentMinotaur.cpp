#include "HexusOpponentMinotaur.h"

const std::string HexusOpponentMinotaur::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MINOTAUR";
HexusOpponentMinotaur* HexusOpponentMinotaur::instance = nullptr;

HexusOpponentMinotaur* HexusOpponentMinotaur::getInstance()
{
	if (HexusOpponentMinotaur::instance == nullptr)
	{
		HexusOpponentMinotaur::instance = new HexusOpponentMinotaur();
	}

	return HexusOpponentMinotaur::instance;
}

HexusOpponentMinotaur::HexusOpponentMinotaur() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Minotaur_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-64.0f, -80.0f),
	HexusOpponentMinotaur::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
	},
	HexusOpponentData::generateDeck(25, 0, 5, 0.33f, 0.33f,
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

HexusOpponentMinotaur::~HexusOpponentMinotaur()
{
}
