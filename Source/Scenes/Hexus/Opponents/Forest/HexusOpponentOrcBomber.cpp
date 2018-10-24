#include "HexusOpponentOrcBomber.h"

const std::string HexusOpponentOrcBomber::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_BOMBER";
HexusOpponentOrcBomber* HexusOpponentOrcBomber::instance = nullptr;

HexusOpponentOrcBomber* HexusOpponentOrcBomber::getInstance()
{
	if (HexusOpponentOrcBomber::instance == nullptr)
	{
		HexusOpponentOrcBomber::instance = new HexusOpponentOrcBomber();
	}

	return HexusOpponentOrcBomber::instance;
}

HexusOpponentOrcBomber::HexusOpponentOrcBomber() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_OrcBomber_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentOrcBomber::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.345f),
	HexusOpponentData::generateDeck(25, 0.345f,
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

HexusOpponentOrcBomber::~HexusOpponentOrcBomber()
{
}
