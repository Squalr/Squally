#include "HexusOpponentTutorialE.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"

using namespace cocos2d;

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

HexusOpponentTutorialE::HexusOpponentTutorialE() : super(
	EntityResources::Npcs_BalmerPeaks_Irmik_Animations,
	HexusResources::Menus_HexusFrameBalmerPeaks,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -144.0f),
	Vec2(0.0f, -24.0f),
	HexusOpponentTutorialE::OpponentSaveKey,
	super::Strategy::Random,
	Card::CardStyle::Water,
	0.0f,
	super::generateDeck(25, 0.0f,
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Hex12),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex15),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
		})
	)
{
}

HexusOpponentTutorialE::~HexusOpponentTutorialE()
{
}
