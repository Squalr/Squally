//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Lioness.h"

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

const std::string Lioness::MapKeyLioness = "lioness";
HexusOpponentData* Lioness::HexusOpponentDataInstance = nullptr;
const std::string Lioness::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LIONESS";

Lioness* Lioness::deserialize(ValueMap& initProperties)
{
	Lioness* instance = new Lioness(initProperties);

	instance->autorelease();

	return instance;
}

Lioness::Lioness(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_Lioness_Animations,
	EntityResources::Enemies_UnderflowRuins_Lioness_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 278.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Lioness::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Lioness::~Lioness()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Lioness::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Lioness::getHexusOpponentData()
{
	if (Lioness::HexusOpponentDataInstance == nullptr)
	{
		Lioness::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_Lioness_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Lioness::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.250f,
			HexusOpponentData::generateDeck(32, 0.250f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Lioness::HexusOpponentDataInstance;
}