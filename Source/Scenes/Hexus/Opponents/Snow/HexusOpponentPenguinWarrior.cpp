#include "HexusOpponentPenguinWarrior.h"

const std::string HexusOpponentPenguinWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PENGUIN_WARRIOR";
HexusOpponentPenguinWarrior* HexusOpponentPenguinWarrior::instance = nullptr;

HexusOpponentPenguinWarrior* HexusOpponentPenguinWarrior::getInstance()
{
	if (HexusOpponentPenguinWarrior::instance == nullptr)
	{
		HexusOpponentPenguinWarrior::instance = new HexusOpponentPenguinWarrior();
	}

	return HexusOpponentPenguinWarrior::instance;
}

HexusOpponentPenguinWarrior::HexusOpponentPenguinWarrior() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Enemies_PenguinWarrior_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentPenguinWarrior::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.64f),
	HexusOpponentData::generateDeck(25, 0.64f,
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

HexusOpponentPenguinWarrior::~HexusOpponentPenguinWarrior()
{
}
