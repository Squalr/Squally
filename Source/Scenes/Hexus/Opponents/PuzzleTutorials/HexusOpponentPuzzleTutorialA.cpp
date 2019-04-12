#include "HexusOpponentPuzzleTutorialA.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"

using namespace cocos2d;

const std::string HexusOpponentPuzzleTutorialA::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PUZZLE_TUTORIAL_A";
HexusOpponentPuzzleTutorialA* HexusOpponentPuzzleTutorialA::instance = nullptr;

HexusOpponentPuzzleTutorialA* HexusOpponentPuzzleTutorialA::getInstance()
{
	if (HexusOpponentPuzzleTutorialA::instance == nullptr)
	{
		HexusOpponentPuzzleTutorialA::instance = new HexusOpponentPuzzleTutorialA();
	}

	return HexusOpponentPuzzleTutorialA::instance;
}

HexusOpponentPuzzleTutorialA::HexusOpponentPuzzleTutorialA() : super(
	EntityResources::Npcs_CastleValgrind_KingRedsong_Animations,
	HexusResources::Menus_HexusFrameCastleValgrind,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-48.0f, -144.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentPuzzleTutorialA::OpponentSaveKey,
	super::Strategy::Random,
	Card::CardStyle::Light,
	0.07f,
	super::generateDeck(25, 0.07f,
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
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
		},
		// Enemy deck
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
		},
		// Player hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal11),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
		},
		// Player hex cards
		std::vector<CardData*>
		{
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal11),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
		},
		StateOverride::TutorialMode::TutorialA)
	)
{
}

HexusOpponentPuzzleTutorialA::~HexusOpponentPuzzleTutorialA()
{
}
