//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Mermaid.h"

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

const std::string Mermaid::MapKeyMermaid = "mermaid";
HexusOpponentData* Mermaid::HexusOpponentDataInstance = nullptr;
const std::string Mermaid::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MERMAID";

Mermaid* Mermaid::deserialize(ValueMap& initProperties)
{
	Mermaid* instance = new Mermaid(initProperties);

	instance->autorelease();

	return instance;
}

Mermaid::Mermaid(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_Mermaid_Animations,
	EntityResources::Enemies_UnderflowRuins_Mermaid_Emblem,
	PlatformerCollisionType::Enemy,
	Size(172.0f, 296.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Mermaid::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Mermaid::~Mermaid()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Mermaid::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -180.0f);
}

HexusOpponentData* Mermaid::getHexusOpponentData()
{
	if (Mermaid::HexusOpponentDataInstance == nullptr)
	{
		Mermaid::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_Mermaid_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -180.0f),
			Mermaid::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.750f,
			HexusOpponentData::generateDeck(32, 0.750f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Mov),
CardList::getInstance()->cardListByName.at(CardKeys::Addition),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex15),
CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Mermaid::HexusOpponentDataInstance;
}