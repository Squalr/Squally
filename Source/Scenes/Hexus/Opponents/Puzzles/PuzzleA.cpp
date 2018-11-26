#include "PuzzleA.h"

const std::string PuzzleA::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PUZZLE_A";
PuzzleA* PuzzleA::instance = nullptr;

PuzzleA* PuzzleA::getInstance()
{
	if (PuzzleA::instance == nullptr)
	{
		PuzzleA::instance = new PuzzleA();
	}

	return PuzzleA::instance;
}

PuzzleA::PuzzleA() : HexusOpponentData(
	EntityResources::Platformer_Environment_Castle_Npcs_KingRedsong_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(0.0f, -48.0f),
	PuzzleA::OpponentSaveKey,
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

PuzzleA::~PuzzleA()
{
}
