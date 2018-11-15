#include "HexusOpponentYetiWarrior.h"

const std::string HexusOpponentYetiWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YETI_WARRIOR";
HexusOpponentYetiWarrior* HexusOpponentYetiWarrior::instance = nullptr;

HexusOpponentYetiWarrior* HexusOpponentYetiWarrior::getInstance()
{
	if (HexusOpponentYetiWarrior::instance == nullptr)
	{
		HexusOpponentYetiWarrior::instance = new HexusOpponentYetiWarrior();
	}

	return HexusOpponentYetiWarrior::instance;
}

HexusOpponentYetiWarrior::HexusOpponentYetiWarrior() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Enemies_YetiWarrior_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.5f,
	Vec2(-48.0f, -72.0f),
	Vec2(-24.0f, -64.0f),
	HexusOpponentYetiWarrior::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.65f),
	HexusOpponentData::generateDeck(25, 0.65f,
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

HexusOpponentYetiWarrior::~HexusOpponentYetiWarrior()
{
}
