#include "HexusOpponentTutorialB.h"

const std::string HexusOpponentTutorialB::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_B";
HexusOpponentTutorialB* HexusOpponentTutorialB::instance = nullptr;

HexusOpponentTutorialB* HexusOpponentTutorialB::getInstance()
{
	if (HexusOpponentTutorialB::instance == nullptr)
	{
		HexusOpponentTutorialB::instance = new HexusOpponentTutorialB();
	}

	return HexusOpponentTutorialB::instance;
}

HexusOpponentTutorialB::HexusOpponentTutorialB() : HexusOpponentData(
	EntityResources::Environment_Obelisk_Npcs_PrincessNebea_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentTutorialB::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Air,
	HexusOpponentData::generateReward(0.075f),
	HexusOpponentData::generateDeck(25, 0.075f,
	{
	}),
	StateOverride::create(
		// Player losses
		1,
		// Enemy losses
		0,
		// Player's turn
		true,
		// Player passed
		false,
		// Enemy passed
		false,
		// Player deck
		std::vector<CardData*>
		{
		},
		// Enemy deck
		std::vector<CardData*>
		{
		},
		// Player hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal15),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
		},
		// Player binary cards
		std::vector<CardData*>
		{
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal9),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Hex12),
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		},
		StateOverride::TutorialMode::TutorialB)
	)
{
}

HexusOpponentTutorialB::~HexusOpponentTutorialB()
{
}
