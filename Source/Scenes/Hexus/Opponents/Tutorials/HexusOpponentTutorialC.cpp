#include "HexusOpponentTutorialC.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"

using namespace cocos2d;

const std::string HexusOpponentTutorialC::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_C";
HexusOpponentTutorialC* HexusOpponentTutorialC::instance = nullptr;

HexusOpponentTutorialC* HexusOpponentTutorialC::getInstance()
{
	if (HexusOpponentTutorialC::instance == nullptr)
	{
		HexusOpponentTutorialC::instance = new HexusOpponentTutorialC();
	}

	return HexusOpponentTutorialC::instance;
}

HexusOpponentTutorialC::HexusOpponentTutorialC() : super(
	EntityResources::Npcs_SeaSharpCaverns_Alder_Animations,
	HexusResources::Menus_HexusFrameSeaSharpCaverns,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -144.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentTutorialC::OpponentSaveKey,
	super::Strategy::Random,
	Card::CardStyle::Earth,
	0.085f,
	super::generateDeck(25, 0.085f,
	{
	}),
	StateOverride::create(
		// Player losses
		0,
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
		},
		// Enemy deck
		std::vector<CardData*>
		{
		},
		// Player hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary14),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
		},
		StateOverride::TutorialMode::TutorialC)
	)
{
}

HexusOpponentTutorialC::~HexusOpponentTutorialC()
{
}
