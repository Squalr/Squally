#include "HexusOpponentReanimatedFighter.h"

const std::string HexusOpponentReanimatedFighter::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_REANIMATED_FIGHTER";
HexusOpponentReanimatedFighter* HexusOpponentReanimatedFighter::instance = nullptr;

HexusOpponentReanimatedFighter* HexusOpponentReanimatedFighter::getInstance()
{
	if (HexusOpponentReanimatedFighter::instance == nullptr)
	{
		HexusOpponentReanimatedFighter::instance = new HexusOpponentReanimatedFighter();
	}

	return HexusOpponentReanimatedFighter::instance;
}

HexusOpponentReanimatedFighter::HexusOpponentReanimatedFighter() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_ReanimatedFighter_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -32.0f),
	Vec2(-48.0f, -32.0f),
	HexusOpponentReanimatedFighter::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.845f),
	HexusOpponentData::generateDeck(25, 0.845f,
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

HexusOpponentReanimatedFighter::~HexusOpponentReanimatedFighter()
{
}
