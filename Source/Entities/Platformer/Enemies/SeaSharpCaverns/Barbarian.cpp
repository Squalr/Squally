//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Barbarian.h"

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

const std::string Barbarian::MapKeyBarbarian = "barbarian";
HexusOpponentData* Barbarian::HexusOpponentDataInstance = nullptr;
const std::string Barbarian::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BARBARIAN";

Barbarian* Barbarian::deserialize(ValueMap& initProperties)
{
	Barbarian* instance = new Barbarian(initProperties);

	instance->autorelease();

	return instance;
}

Barbarian::Barbarian(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_Barbarian_Animations,
	EntityResources::Enemies_SeaSharpCaverns_Barbarian_Emblem,
	PlatformerCollisionType::Enemy,
	Size(1280.0f, 920.0f),
	1.0f,
	Vec2(-32.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Barbarian::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Barbarian::~Barbarian()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Barbarian::getAvatarFrameOffset()
{
	return Vec2(0.0f, -160.0f);
}

HexusOpponentData* Barbarian::getHexusOpponentData()
{
	if (Barbarian::HexusOpponentDataInstance == nullptr)
	{
		Barbarian::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_Barbarian_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(-32.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(0.0f, -160.0f),
			Barbarian::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.083f,
			HexusOpponentData::generateDeck(32, 0.083f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Barbarian::HexusOpponentDataInstance;
}