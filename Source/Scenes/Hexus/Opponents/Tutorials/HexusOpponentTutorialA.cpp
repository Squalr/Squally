#include "HexusOpponentTutorialA.h"

const std::string HexusOpponentTutorialA::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_A";
HexusOpponentTutorialA* HexusOpponentTutorialA::instance = nullptr;

HexusOpponentTutorialA* HexusOpponentTutorialA::getInstance()
{
	if (HexusOpponentTutorialA::instance == nullptr)
	{
		HexusOpponentTutorialA::instance = new HexusOpponentTutorialA();
	}

	return HexusOpponentTutorialA::instance;
}

HexusOpponentTutorialA::HexusOpponentTutorialA() : HexusOpponentData(
	EntityResources::Npcs_KingRedsong_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentTutorialA::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Light,
	HexusOpponentData::generateReward(0.07f),
	HexusOpponentData::generateDeck(25, 0.07f,
	{
	}),
	StateOverride::create(
		// Player losses
		1,
		// Enemy losses
		1,
		// Player's turn
		true,
		// Player passed
		false,
		// Enemy passed
		true,
		// Player deck
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		},
		// Enemy deck
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		},
		// Player hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Binary12),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
		},
		// Enemy hand
		std::vector<CardData*>
		{
		},
		// Player binary cards
		std::vector<CardData*>
		{
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		},
		// Player hex cards
		std::vector<CardData*>
		{
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
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal11),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Hex13),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
		},
		StateOverride::TutorialMode::TutorialA)
	)
{
}

HexusOpponentTutorialA::~HexusOpponentTutorialA()
{
}
