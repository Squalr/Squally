#include "HexusOpponentTutorialF.h"

const std::string HexusOpponentTutorialF::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_F";
HexusOpponentTutorialF* HexusOpponentTutorialF::instance = nullptr;

HexusOpponentTutorialF* HexusOpponentTutorialF::getInstance()
{
	if (HexusOpponentTutorialF::instance == nullptr)
	{
		HexusOpponentTutorialF::instance = new HexusOpponentTutorialF();
	}

	return HexusOpponentTutorialF::instance;
}

HexusOpponentTutorialF::HexusOpponentTutorialF() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Griffin_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, -24.0f),
	HexusOpponentTutorialF::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Light,
	HexusOpponentData::generateReward(0.1f),
	HexusOpponentData::generateDeck(25, 0.1f,
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
			CardList::getInstance()->cardListByName->at(CardKeys::Mov),
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
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
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
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
			CardList::getInstance()->cardListByName->at(CardKeys::Decimal15),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
		},
		StateOverride::TutorialMode::TutorialF)
	)
{
}

HexusOpponentTutorialF::~HexusOpponentTutorialF()
{
}
