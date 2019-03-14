#include "HexusOpponentTutorialB.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

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
	EntityResources::Npcs_LambdaCrypts_PrincessNebea_Animations,
	UIResources::Menus_Hexus_HexusFrameVoidStar,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -144.0f),
	Vec2(0.0f, -48.0f),
	HexusOpponentTutorialB::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Air,
	0.075f,
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
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
		},
		// Player binary cards
		std::vector<CardData*>
		{
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
		},
		// Player hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex12),
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
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
		},
		StateOverride::TutorialMode::TutorialB)
	)
{
}

HexusOpponentTutorialB::~HexusOpponentTutorialB()
{
}
