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
	Vec2(-48.0f, -144.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentYetiWarrior::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 10, 0.33f, 0.33f,
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
