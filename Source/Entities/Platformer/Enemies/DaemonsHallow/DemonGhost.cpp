//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonGhost.h"

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

const std::string DemonGhost::MapKeyDemonGhost = "demon-ghost";
HexusOpponentData* DemonGhost::HexusOpponentDataInstance = nullptr;
const std::string DemonGhost::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_GHOST";

DemonGhost* DemonGhost::deserialize(ValueMap& initProperties)
{
	DemonGhost* instance = new DemonGhost(initProperties);

	instance->autorelease();

	return instance;
}

DemonGhost::DemonGhost(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonGhost_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonGhost_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 320.0f),
	0.7f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = DemonGhost::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

DemonGhost::~DemonGhost()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 DemonGhost::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* DemonGhost::getHexusOpponentData()
{
	if (DemonGhost::HexusOpponentDataInstance == nullptr)
	{
		DemonGhost::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonGhost_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.7f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonGhost::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.500f,
			HexusOpponentData::generateDeck(32, 0.500f,
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
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return DemonGhost::HexusOpponentDataInstance;
}