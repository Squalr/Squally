#include "HexusOpponentReanimatedPig.h"

const std::string HexusOpponentReanimatedPig::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_REANIMATED_PIG";
HexusOpponentReanimatedPig* HexusOpponentReanimatedPig::instance = nullptr;

HexusOpponentReanimatedPig* HexusOpponentReanimatedPig::getInstance()
{
	if (HexusOpponentReanimatedPig::instance == nullptr)
	{
		HexusOpponentReanimatedPig::instance = new HexusOpponentReanimatedPig();
	}

	return HexusOpponentReanimatedPig::instance;
}

HexusOpponentReanimatedPig::HexusOpponentReanimatedPig() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_ReanimatedPig_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentReanimatedPig::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
	},
	HexusOpponentData::generateDeck(25, 0.1f,
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

HexusOpponentReanimatedPig::~HexusOpponentReanimatedPig()
{
}
