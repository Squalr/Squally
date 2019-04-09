//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Rhinoman.h"

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

const std::string Rhinoman::MapKeyRhinoman = "rhinoman";
HexusOpponentData* Rhinoman::HexusOpponentDataInstance = nullptr;
const std::string Rhinoman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RHINOMAN";

Rhinoman* Rhinoman::deserialize(ValueMap& initProperties)
{
	Rhinoman* instance = new Rhinoman(initProperties);

	instance->autorelease();

	return instance;
}

Rhinoman::Rhinoman(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_Rhinoman_Animations,
	EntityResources::Enemies_SeaSharpCaverns_Rhinoman_Emblem,
	PlatformerCollisionType::Enemy,
	Size(592.0f, 592.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	35,
	8)
{
	this->hexusOpponentData = Rhinoman::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Rhinoman::~Rhinoman()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Rhinoman::getAvatarFrameOffset()
{
	return Vec2(-64.0f, -288.0f);
}

HexusOpponentData* Rhinoman::getHexusOpponentData()
{
	if (Rhinoman::HexusOpponentDataInstance == nullptr)
	{
		Rhinoman::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_Rhinoman_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -312.0f),
			Vec2(-64.0f, -288.0f),
			Rhinoman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
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

	return Rhinoman::HexusOpponentDataInstance;
}