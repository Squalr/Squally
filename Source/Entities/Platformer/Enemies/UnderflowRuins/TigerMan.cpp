//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "TigerMan.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

using namespace cocos2d;

const std::string TigerMan::MapKeyTigerMan = "tiger-man";
HexusOpponentData* TigerMan::HexusOpponentDataInstance = nullptr;
const std::string TigerMan::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TIGER_MAN";

TigerMan* TigerMan::deserialize(ValueMap& initProperties)
{
	TigerMan* instance = new TigerMan(initProperties);

	instance->autorelease();

	return instance;
}

TigerMan::TigerMan(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_TigerMan_Animations,
	EntityResources::Enemies_UnderflowRuins_TigerMan_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 308.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	23,
	18)
{
	this->hexusOpponentData = TigerMan::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

TigerMan::~TigerMan()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 TigerMan::getAvatarFrameOffset()
{
	return Vec2(-16.0f, -212.0f);
}

HexusOpponentData* TigerMan::getHexusOpponentData()
{
	if (TigerMan::HexusOpponentDataInstance == nullptr)
	{
		TigerMan::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_TigerMan_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-16.0f, -212.0f),
			TigerMan::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.583f,
			HexusOpponentData::generateDeck(32, 0.583f,
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
				true,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return TigerMan::HexusOpponentDataInstance;
}