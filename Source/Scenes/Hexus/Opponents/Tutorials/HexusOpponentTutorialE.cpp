#include "HexusOpponentTutorialE.h"

const std::string HexusOpponentTutorialE::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_E";
HexusOpponentTutorialE* HexusOpponentTutorialE::instance = nullptr;

HexusOpponentTutorialE* HexusOpponentTutorialE::getInstance()
{
	if (HexusOpponentTutorialE::instance == nullptr)
	{
		HexusOpponentTutorialE::instance = new HexusOpponentTutorialE();
	}

	return HexusOpponentTutorialE::instance;
}

HexusOpponentTutorialE::HexusOpponentTutorialE() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Npcs_Irmik_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -24.0f),
	HexusOpponentTutorialE::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Water,
	HexusOpponentData::generateReward(0.095f),
	HexusOpponentData::generateDeck(25, 0.095f,
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
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
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
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		},
		// Player hex cards
		std::vector<CardData*>
		{
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Hex12),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex14),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex15),
			CardList::getInstance()->cardListByName->at(CardKeys::Hex14),
		},
		StateOverride::TutorialMode::TutorialE)
	)
{
}

HexusOpponentTutorialE::~HexusOpponentTutorialE()
{
}
