#include "HexusOpponentTutorialD.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"

using namespace cocos2d;

const std::string HexusOpponentTutorialD::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TUTORIAL_D";
HexusOpponentTutorialD* HexusOpponentTutorialD::instance = nullptr;

HexusOpponentTutorialD* HexusOpponentTutorialD::getInstance()
{
	if (HexusOpponentTutorialD::instance == nullptr)
	{
		HexusOpponentTutorialD::instance = new HexusOpponentTutorialD();
	}

	return HexusOpponentTutorialD::instance;
}

HexusOpponentTutorialD::HexusOpponentTutorialD() : super(
	EntityResources::Npcs_LambdaCrypts_Zana_Animations,
	HexusResources::Menus_HexusFrameVoidStar,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -144.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentTutorialD::OpponentSaveKey,
	super::Strategy::Random,
	Card::CardStyle::Earth,
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
		false,
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
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
		},
		// Enemy hand
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex8),
		},
		// Player binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
		},
		// Player decimal cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex12),
		},
		// Player hex cards
		std::vector<CardData*>
		{
		},
		// Enemy binary cards
		std::vector<CardData*>
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
			CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
		},
		// Enemy decimal cards
		std::vector<CardData*>
		{
		},
		// Enemy hex cards
		std::vector<CardData*>
		{
		},
		StateOverride::TutorialMode::TutorialD)
	)
{
}

HexusOpponentTutorialD::~HexusOpponentTutorialD()
{
}
